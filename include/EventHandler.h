//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_EVENTHANDLER_H
#define YADROIMPULS_EVENTHANDLER_H

#include "Event.h"

struct Table {
    int income{0};
    int time{0};
    int lastTimeArrival{0};
    bool free{true};

};

class EventHandler {
    static void generateEvent(int time, int id, const std::string &error, const std::string &additional);
    static int getDuration(int first,int second, int timeOpen, int timeClose);

public:
    static void process(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events);
};

#endif //YADROIMPULS_EVENTHANDLER_H
