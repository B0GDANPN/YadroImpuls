cmake_minimum_required(VERSION 3.28)
project(YadroImpuls)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(../include)
include_directories(../src)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

include(GoogleTest)

add_executable(testSolution
        main.cpp
        ../include/Parser.h
        ../src/Parser.cpp
        ../include/EventHandler.h
        ../src/EventHandler.cpp
        ../include/Event.h
        ../src/Event.cpp
        ../include/Validator.h
        ../src/Validator.cpp)
target_link_libraries(
        testSolution
        GTest::gtest_main
)
gtest_discover_tests(testSolution)