//
// Created by bogdan on 15.05.24.
//
#include "Validator.h"

bool Validator::isValidName(const std::string &name) {
    return std::all_of(name.begin(), name.end(), [](char c) {
        return (std::islower(c) || std::isdigit(c) || c == '_' || c == '-');
    });
}

bool Validator::isValidTime(int first, int second, int timeOpen, int timeClose) {
    if (timeOpen > timeClose) {// случай когда клуб открывается и закрывается в разные сутки
        if (first <= timeClose) {
            first += lastTime;
        }
        if (second <= timeClose) {
            second += lastTime;
        }
        timeClose += lastTime;
    }
    if ((timeOpen <= first && first <= timeClose) && (timeOpen <= second && second <= timeClose)) {
        return first <= second;// оба события во время работы
    } else if (!(timeOpen <= first && first <= timeClose) && !(timeOpen <= second && second <= timeClose)) {
        return first <= second; //вне работы
    }
    return true; //если одно из событий произошло вне времени работы, то нет смысла рассматривать случай
}

int Validator::validate(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events) {
    /*В каждом Event уже правильно введены время и id, неправильные варианты ввода отлавливает Parser
     * Validator проверяет содержимое body Event и соответствие кол-ву столов, и остальные входные условия
     * */
    if (N <= 0) { return 0; }
    if (timeOpen <= 0 || timeClose <= 0) {
        return 1;
    }
    if (costHour <= 0) {
        return 2;
    }
    for (int i = 0; i < events.size(); ++i) {
        if (i >= 1 && !isValidTime(events[i - 1].time, events[i].time, timeOpen, timeClose)) {
            return i + 3;
        }
        if (!(1 <= events[i].id && events[i].id <= 4)) {
            return i + 3;
        }
        size_t bodySize = events[i].body.size();
        if (events[i].id == 2) {
            if (bodySize != 2) {
                return i + 3;
            }
        } else {
            if (bodySize != 1) {
                return i + 3;
            }
        }
        std::string name = events[i].body[0];
        if (!isValidName(name)) {
            return i + 3;
        }
        if (events[i].id == 2) {
            int numTable;
            try {
                numTable = std::stoi(events[i].body[1]);
            }
            catch (const std::exception &ex) {
                return i + 3;
            }
            if (!(1 <= numTable && numTable <= N)) {
                return i + 3;
            }
        }

    }
    return -1;
}

