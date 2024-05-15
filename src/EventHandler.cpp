//
// Created by bogdan on 15.05.24.
//
#include <iostream>
#include "EventHandler.h"
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

void EventHandler::process(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events) {
    std::map<int, Table> infoTables;
    std::set<std::string> clients;
    std::map<std::string, int> clientTable; //для подсчёта выручки при смене стола
    std::queue<std::string> waitingList;
    for (int i = 1; i <= N; ++i) {
        infoTables[i] = Table{};
    }
    std::cout << timeOpen << std::endl;
    std::string name;
    int numberTable;
    for (Event event: events) {
        std::cout << event.toStr() << std::endl;
        switch (event.id) {
            case 1:
                name = event.body[0];
                if (clients.contains(name)) {
                    generateEvent(event.time, 13, "YouShallNotPass");
                    continue;
                }
                if (!(timeOpen <= event.time && event.time <= timeClose)) {
                    generateEvent(event.time, 13, "NotOpenYet");
                    continue;
                }
                waitingList.push(name);
                clients.insert(name);
                break;
            case 2:
                name = event.body[0];
                if (!clients.contains(name)) {
                    generateEvent(event.time, 13, "ClientUnknown");
                    continue;
                }
                numberTable = std::stoi(event.body[1]);
                if (!infoTables[numberTable].free) {
                    generateEvent(event.time, 13, "PlacelsBusy");
                    continue;
                }
                if (clientTable.contains(name)) { //клиент меняет стол
                    int oldNumberTable = clientTable[name];
                    infoTables[oldNumberTable].free = 1;
                    int currentDuration = ceil(
                            static_cast<double>(event.time - infoTables[oldNumberTable].lastTimeArrival) / 60);
                    infoTables[oldNumberTable].income += currentDuration * costHour;
                    infoTables[oldNumberTable].time += event.time - infoTables[oldNumberTable].lastTimeArrival;
                } else { //новый клиент садится за стол
                    waitingList.pop();
                }
                clientTable[name] = numberTable;
                infoTables[numberTable].free = 0;
                infoTables[numberTable].lastTimeArrival = event.time;
                break;
            case 3:
                name = event.body[0];
                if (existFreeTable(infoTables)) {
                    generateEvent(event.time, 13, "ICanWaitNoLonger!");
                    continue;
                }
                if (waitingList.size() > N) {
                    generateEvent(event.time, 11, name);
                }
                break;
            case 4:
                name = event.body[0];
                if (!clients.contains(name)) {
                    generateEvent(event.time, 13, "ClientUnknown");
                    continue;
                }
                clients.erase(name);
                int oldNumberTable = clientTable[name];
                clientTable.erase(name);
                infoTables[oldNumberTable].free = 1;
                int currentDuration = ceil(
                        static_cast<double>(event.time - infoTables[oldNumberTable].lastTimeArrival) / 60);
                infoTables[oldNumberTable].income += currentDuration * costHour;
                infoTables[oldNumberTable].time += event.time - infoTables[oldNumberTable].lastTimeArrival;
                if (!waitingList.empty()) {
                    generateEvent(event.time, 12, name, " " + std::to_string(oldNumberTable));
                }
                break;
        }
    }
    for (const auto &remainingClient: clients) {
        generateEvent(timeClose, 11, remainingClient);
    }
    std::cout << timeClose << std::endl;
    for (const auto &[number, table]: infoTables) {
        std::cout << number << ' ' << table.income << Event::timeToStr(table.time) << std::endl;
    }
}

