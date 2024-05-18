#include "gtest/gtest.h"
#include "testEvent.cpp"
#include "testParser.cpp"
#include "testValidator.cpp"
#include "testEventHandler.cpp"
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}