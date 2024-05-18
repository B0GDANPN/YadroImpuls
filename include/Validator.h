#ifndef YADROIMPULS_VALIDATOR_H
#define YADROIMPULS_VALIDATOR_H

#include "Event.h"

class Validator {// все методы публичные для тестов

public:
    static int validate(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events);

    static bool isValidTime(int first, int second, int timeOpen, int timeClose);

    static bool isValidName(const std::string &name);
};


#endif //YADROIMPULS_VALIDATOR_H
