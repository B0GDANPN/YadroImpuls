#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"

bool isValidData(const std::vector<Event> &events) {
    return true;
}

int main(int argc, char *argv[]) {
    const char *filename = argv[1];
    std::ifstream file(filename);
    std::string tmp;
    file >> tmp;
    int N = Parser::getInt(tmp);
    file >> tmp;
    int timeOpen = Parser::getTime(tmp);
    file >> tmp;
    int timeClose = Parser::getTime(tmp);
    int costHour;
    file >> costHour;
    std::vector<Event> events = Parser::getEvents(N, file);
    file.close();
    return 0;
}