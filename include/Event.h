//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_EVENT_H
#define YADROIMPULS_EVENT_H

#include <sstream>

struct Event {
    int time;
    int id;
    std::vector<std::string> body;

    static std::string timeToStr(int time_) {
        int hours = time_ / 60;
        int minutes = time_ % 60;
        std::string hStr = hours > 9 ? std::to_string(hours) : '0' + std::to_string(hours);
        std::string mStr = hours > 9 ? std::to_string(minutes) : '0' + std::to_string(minutes);
        return hStr + ':' + mStr;
    }

    std::string toStr() {
        std::ostringstream ss;
        std::string timeStr = timeToStr(time);
        std::string idStr = std::to_string(id);
        ss << timeStr << ' ' << idStr;
        for (const auto &el: body) {
            ss << ' ' << el;
        }
        return ss.str();
    }
};

#endif //YADROIMPULS_EVENT_H
