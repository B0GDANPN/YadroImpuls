//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_PARSER_H
#define YADROIMPULS_PARSER_H

#include "Event.h"
#include <string>
#include <sstream>

class Parser {
    static Event getEvent(const std::string &str);

public:
    static int getTime(const std::string &stringTime);

    static std::vector<Event> getEvents(std::ifstream &file);

    static int getInt(const std::string &str);
};


#endif //YADROIMPULS_PARSER_H
