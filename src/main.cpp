#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"
#include "Validator.h"
#include "EventHandler.h"

int main(int argc, char *argv[]) {
    const char *filename = argv[1];
    std::ifstream file(filename);
    std::string tmp;
    file >> tmp;
    try {
        int N = Parser::getInt(tmp);
        file >> tmp;
        int timeOpen = Parser::getTime(tmp);
        file >> tmp;
        int timeClose = Parser::getTime(tmp);
        file >> tmp;
        int costHour = Parser::getTime(tmp);
        std::vector<Event> events = Parser::getEvents(file);
        int indexInvalid = Validator::validate(N, timeOpen, timeClose, costHour,
                                               events); //-1 данные удовлетворяют формату, иначе нет
        if (indexInvalid != -1) {
            switch (indexInvalid) {
                case 0:
                    std::cout << std::to_string(N) << std::endl;
                    break;
                case 1:
                    std::cout << std::to_string(timeOpen) << ' ' << std::to_string(timeClose) << std::endl;
                    break;
                case 2:// если событий нету то будет выведено стоимость часа - последняя строка с данными
                    std::cout << std::to_string(costHour) << std::endl;
                    break;
                default:
                    indexInvalid -= 3;
                    std::string invalidString = events[indexInvalid].toStr();
                    std::cout << invalidString << std::endl;
            }
        } else {
            EventHandler::process(N, timeOpen, timeClose, costHour,
                       events);
        }
    }
    catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
    }
    file.close();
    return 0;
}