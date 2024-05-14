//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_VALIDATOR_H
#define YADROIMPULS_VALIDATOR_H

#include "Event.h"
#include <algorithm>

class Validator {

    static bool isValidName(const std::string &name) {
        return std::all_of(name.begin(), name.end(), [](char c) {
            return (std::islower(c) || std::isdigit(c) || c == '_' || c == '-');
        });
    }

public:
    static int validate(int N, int timeOpen, int timeClose, int costHour,const std::vector<Event>& events) {
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
        if (events.size() < N) {// если
            return 3 + static_cast<int>(events.size()) - 1;
        }
        for (int i = 0; i < events.size(); ++i) {
            if (!(1 <= events[i].id && events[i].id <= 4)) {
                return i;
            }
            size_t bodySize = events[i].body.size();
            if (!(1 <= bodySize && bodySize <= 2)) {
                return i;
            }
            std::string name = events[i].body[0];
            if (!isValidName(name)) {
                return i;
            }
            if (events[i].id == 2) {
                if (bodySize == 2) {
                    int numTable;
                    try {
                        numTable = std::stoi(events[i].body[1]);
                    }
                    catch (const std::exception &ex) {
                        return i;
                    }
                    if (!(1 <= numTable && numTable <= N)) {
                        return i;
                    }
                } else {
                    return i;
                }
            }

        }
        return -1;
    }
};


#endif //YADROIMPULS_VALIDATOR_H
