cmake_minimum_required(VERSION 3.22)
project(YadroImpuls)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)
include_directories(src)
include_directories(tst)
add_executable(solution
        src/main.cpp
        include/Parser.h
        src/Parser.cpp
        include/EventHandler.h
        src/EventHandler.cpp
        include/Event.h
        src/Event.cpp
        include/Validator.h
        src/Validator.cpp)
