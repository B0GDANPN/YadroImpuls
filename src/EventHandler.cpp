//
// Created by bogdan on 15.05.24.
//
#include "EventHandler.h"
#include <iostream>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>

void EventHandler::generateEvent(int time, int id, const std::string &msg, const std::string &additional = "") {
    std::string timeStr = Event::timeToStr(time);
    std::cout << timeStr << ' ' << id << ' ' << msg << additional << std::endl;
}

bool existFreeTable(const std::map<int, Table> &infoTables) {
    return std::ranges::any_of(infoTables, [](const auto &item) {
        return item.second.free;
    });
}

int EventHandler::getDuration(int first, int second, int timeOpen, int timeClose) { //гарантируется first<=second
    if (timeOpen > timeClose) {// случай когда клуб открывается и закрывается в разные сутки
        if (first <= timeClose) {
            first += lastTime;
        }
        if (second <= timeClose) {
            second += lastTime;
        }
    }
    return second - first;
}

void EventHandler::process(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events) {
    std::map<int, Table> infoTables;
    std::set<std::string> clients;
    std::map<std::string, int> clientTable; //для подсчёта выручки при смене стола
    std::deque<std::string> waitingList; // можно было б использовать queue, но при id 3 может потребоваться удалять не с начала очереди
    for (int i = 1; i <= N; ++i) {
        infoTables[i] = Table{};
    }
    std::cout << Event::timeToStr(timeOpen) << std::endl;
    std::string tmpName;
    int tmpNumTable;
    for (const auto &event: events) {
        std::cout << event.toStr() << std::endl;
        switch (event.id) {
            case 1:
                tmpName = event.body[0];
                if (clients.contains(tmpName)) {
                    generateEvent(event.time, 13, "YouShallNotPass");
                    continue;
                }
                if (timeOpen <= timeClose) {
                    if (!(timeOpen <= event.time && event.time <= timeClose)) {
                        generateEvent(event.time, 13, "NotOpenYet");
                        continue;
                    }
                } else {
                    if (!(timeOpen <= event.time || event.time <= timeClose)) {
                        generateEvent(event.time, 13, "NotOpenYet");
                        continue;
                    }
                }
                waitingList.push_back(tmpName);
                clients.insert(tmpName);
                break;
            case 2:
                tmpName = event.body[0];
                if (!clients.contains(tmpName)) {
                    generateEvent(event.time, 13, "ClientUnknown");
                    continue;
                }
                tmpNumTable = std::stoi(event.body[1]);
                if (!infoTables[tmpNumTable].free) {
                    generateEvent(event.time, 13, "PlacelsBusy");
                    continue;
                }
                if (clientTable.contains(tmpName)) { //клиент меняет стол
                    int oldNumberTable = clientTable[tmpName];
                    infoTables[oldNumberTable].free = true;

                    int duration = getDuration(infoTables[oldNumberTable].lastTimeArrival, event.time, timeOpen,
                                               timeClose);
                    infoTables[oldNumberTable].income +=
                            costHour * static_cast<int>(ceil(static_cast<double>(duration) / 60));
                    infoTables[oldNumberTable].time += duration;
                } else { //новый клиент садится за стол
                    waitingList.pop_front();
                }
                clientTable[tmpName] = tmpNumTable;
                infoTables[tmpNumTable].free = false;
                infoTables[tmpNumTable].lastTimeArrival = event.time;
                break;
            case 3:
                tmpName = event.body[0];
                if (existFreeTable(infoTables)) {
                    generateEvent(event.time, 13, "ICanWaitNoLonger!");
                    continue;
                }
                if (waitingList.size() > N) {
                    generateEvent(event.time, 11, tmpName);
                    auto it = std::find(waitingList.begin(), waitingList.end(), tmpName);
                    waitingList.erase(it);
                    clients.erase(tmpName);
                }
                break;
            case 4:
                tmpName = event.body[0];
                if (!clients.contains(tmpName)) {
                    generateEvent(event.time, 13, "ClientUnknown");
                    continue;
                }
                clients.erase(tmpName);
                if (!clientTable.contains(tmpName)) { // клиент мог просто стоять в очереди
                    continue;
                }
                int oldNumberTable = clientTable[tmpName];
                clientTable.erase(tmpName);
                infoTables[oldNumberTable].free = true;

                int duration = getDuration(infoTables[oldNumberTable].lastTimeArrival, event.time, timeOpen,
                                           timeClose);
                infoTables[oldNumberTable].income +=
                        costHour * static_cast<int>(ceil(static_cast<double>(duration) / 60));
                infoTables[oldNumberTable].time += duration;
                if (!waitingList.empty()) {
                    generateEvent(event.time, 12, tmpName, " " + std::to_string(oldNumberTable));
                    tmpName = waitingList.front();
                    waitingList.pop_front();
                    clientTable[tmpName] = oldNumberTable;
                    infoTables[oldNumberTable].free = false;
                    infoTables[oldNumberTable].lastTimeArrival = event.time;
                }
                break;
        }
    }
    for (const auto &remainingClient: clients) {
        if (!clientTable.contains(remainingClient)) {// клуб закрылся когда клиент был в очереди
            continue;
        }
        generateEvent(timeClose, 11, remainingClient);
        int oldNumberTable = clientTable[remainingClient];
        infoTables[oldNumberTable].free = true;
        int duration = getDuration(infoTables[oldNumberTable].lastTimeArrival, timeClose, timeOpen, timeClose);
        infoTables[oldNumberTable].income += costHour * static_cast<int>(ceil(static_cast<double>(duration) / 60));
        infoTables[oldNumberTable].time += duration;
    }
    std::cout << Event::timeToStr(timeClose) << std::endl;
    for (const auto &[number, table]: infoTables) {
        std::cout << number << ' ' << table.income << ' ' << Event::timeToStr(table.time) << std::endl;
    }
}
