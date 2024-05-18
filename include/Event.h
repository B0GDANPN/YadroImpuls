//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_EVENT_H
#define YADROIMPULS_EVENT_H

#include <sstream>
#include <vector>

const int lastTime = 1439; // 23:59
struct Event {
    int time;
    int id;
    std::vector<std::string> body;

    static std::string timeToStr(int time_);

    std::string toStr() const;
};

#endif //YADROIMPULS_EVENT_H
