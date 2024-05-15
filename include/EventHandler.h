//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_EVENTHANDLER_H
#define YADROIMPULS_EVENTHANDLER_H

#include <map>
#include "Parser.h"
#include <queue>
struct Table {
    int free{1};
    int income{0};
    int time{0};
    int lastTimeArrival{0};

};
class EventHandler {
    static void generateEvent(int time,int id,const std::string &error,const std::string &additional);

public:
    static void process(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events);
};

#endif //YADROIMPULS_EVENTHANDLER_H
