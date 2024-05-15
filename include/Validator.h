//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_VALIDATOR_H
#define YADROIMPULS_VALIDATOR_H

#include "Event.h"
#include <algorithm>

class Validator {

    static bool isValidName(const std::string &name);

public:
    static int validate(int N, int timeOpen, int timeClose, int costHour, const std::vector<Event> &events);
};


#endif //YADROIMPULS_VALIDATOR_H
