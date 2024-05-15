//
// Created by bogdan on 15.05.24.
//
#include <fstream>
#include "Parser.h"

Event Parser::getEvent(const std::string &str) {
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
        std::vector<std::string> body = std::vector(words.begin() + 2, words.end());
        return Event{time, id, body};

    } catch (const std::runtime_error &err) {
        throw std::runtime_error(str); //Чтобы передать в main всю строку, а не подстроку с ошибкой
    }
}

int Parser::getInt(const std::string &str) {
    try {
        int res = stoi(str);
        return res;
    } catch (const std::exception &ex) {
        throw std::runtime_error(str);
    }
}

int Parser::getTime(const std::string &stringTime) {
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

std::vector<Event> Parser::getEvents(std::ifstream &file) {
    std::vector<Event> events;
    std::string tmp;
    while (std::getline(file, tmp)) {
        Event eventTmp = getEvent(tmp);
        events.emplace_back(eventTmp);
    }
    return events;
}

