//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_EVENTHANDLER_H
#define YADROIMPULS_EVENTHANDLER_H

#include <unordered_map>
#include <queue>
#include "Parser.h"

typedef struct {
    int income;
    int time;

} table;

class EventHandler {
public:
    static void procces(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events) {
        std::unordered_map<int, table> infoTables;
        for (int i = 1; i <= N; ++i) {
            infoTables[i] = table{0, 0};
        }
        std::cout << timeOpen << std::endl;
        //events
        std::cout << timeClose << std::endl;
        for (int i = 1; i <= N; ++i) {
            std::cout << i << ' ' << infoTables[i].income << Event::timeToStr(infoTables[i].time) << std::endl;
        }
    }
};


#endif //YADROIMPULS_EVENTHANDLER_H
