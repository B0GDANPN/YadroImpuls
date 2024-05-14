//
// Created by bogdan on 14.05.24.
//

#ifndef YADROIMPULS_PARSER_H
#define YADROIMPULS_PARSER_H

#include "Event.h"
#include <string>
#include <sstream>

class Parser {
    static Event getEvent(const std::string &str) {
        std::istringstream ss(str);
        std::vector<std::string> words;
        std::string tmp;
        while (ss >> tmp) {
            words.emplace_back(tmp);
        }
        if (words.size() < 3) {
            throw std::runtime_error(str);
        }
        try {
            int time = getTime(words[0]);
            int id = getInt(words[1]);
            std::string name = words[2];
            if (id == 2 || id == 12) {
                if (words.size() == 4) {
                    std::string numberTable = words[3];
                    return Event{time, id, {name, numberTable}};
                } else {
                    throw std::runtime_error(str);
                }
            } else {
                return Event{time, id, {name}};
            }

        } catch (const std::runtime_error &err) {
            throw std::runtime_error(str); //Чтобы передать в main всю строку, а не подстроку с ошибкой
        }
        throw std::runtime_error(str); // Должно быть только имя клиента, но
    }

public:
    static int getTime(const std::string &stringTime) {
        std::size_t colonPos = stringTime.find(':');
        if (stringTime.size() != 5 || colonPos != 2) {
            throw std::runtime_error(stringTime);
        }
        try {
            int hours = std::stoi(stringTime.substr(0, colonPos));
            int minutes = std::stoi(stringTime.substr(colonPos + 1));
            return hours * 60 + minutes;
        }
        catch (const std::exception &ex) {
            throw std::runtime_error(stringTime);
        }
    }

    static std::vector<Event> getEvents(int N, const std::ifstream &file) {
        std::vector<Event> events;
        std::string tmp;
        for (int i = 0; i < N; ++i) {
            std::getline(std::cin, tmp);
            if (tmp.empty()) {
                break;
            }
            Event eventTmp = getEvent(tmp);
            events.emplace_back(eventTmp);
        }
        return events;
    }

    static int getInt(const std::string &str) {
        try {
            int res = stoi(str);
            return res;
        } catch (const std::exception &ex) {
            throw std::runtime_error(str);
        }
    }
};


#endif //YADROIMPULS_PARSER_H
