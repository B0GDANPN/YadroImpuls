//
// Created by bogdan on 15.05.24.
//
#include "Event.h"

std::string Event::timeToStr(int time_) {
    int hours = time_ / 60;
    int minutes = time_ % 60;
    std::string hStr = hours > 9 ? std::to_string(hours) : '0' + std::to_string(hours);
    std::string mStr = hours > 9 ? std::to_string(minutes) : '0' + std::to_string(minutes);
    return hStr + ':' + mStr;
}

std::string Event::toStr() {
    std::ostringstream ss;
    std::string timeStr = timeToStr(time);
    std::string idStr = std::to_string(id);
    ss << timeStr << ' ' << idStr;
    for (const auto &el: body) {
        ss << ' ' << el;
    }
    return ss.str();
}

