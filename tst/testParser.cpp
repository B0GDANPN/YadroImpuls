#include <gtest/gtest.h>
#include <fstream>
#include "Parser.h"

class ParserTest : public ::testing::Test {
protected:
    // Helper method to create a temporary file with content
    static std::string createTxt(const std::string& content) {
        std::string filename = std::tmpnam(nullptr);
        std::ofstream file(filename);
        file << content;
        file.close();
        return filename;
    }
};

TEST_F(ParserTest, GetInt_ValidInt) {
    EXPECT_EQ(Parser::getInt("123"), 123);
    EXPECT_EQ(Parser::getInt("0"), 0);
}

TEST_F(ParserTest, GetInt_InvalidInt) {
    EXPECT_THROW(Parser::getInt("abc"), std::runtime_error);
    EXPECT_THROW(Parser::getInt("123abc"), std::runtime_error);
}

TEST_F(ParserTest, GetTime_ValidTime) {
    EXPECT_EQ(Parser::getTime("01:30"), 90);
    EXPECT_EQ(Parser::getTime("23:59"), 1439);
}

TEST_F(ParserTest, GetTime_InvalidTime) {
    EXPECT_THROW(Parser::getTime("24:00"), std::runtime_error);
    EXPECT_THROW(Parser::getTime("00:60"), std::runtime_error);
    EXPECT_THROW(Parser::getTime("1:30"), std::runtime_error);
}

TEST_F(ParserTest, GetEvent_ValidString) {
    Event event = Parser::getEvent("01:30 1 Event 1");
    EXPECT_EQ(event.time, 90);
    EXPECT_EQ(event.id, 1);
    ASSERT_EQ(event.body.size(), 2);
    EXPECT_EQ(event.body[0], "Event");
    EXPECT_EQ(event.body[1], "1");
}

TEST_F(ParserTest, GetEvent_InvalidString) {
    EXPECT_THROW(Parser::getEvent("01:30"), std::runtime_error);
    EXPECT_THROW(Parser::getEvent("01:30 1"), std::runtime_error);
}

TEST_F(ParserTest, GetEvents_ValidFile) {
    std::string filename = createTxt("01:30 1 Event\n02:45 2 Another 3\n");
    std::ifstream file(filename);
    std::vector<Event> events = Parser::getEvents(file);
    file.close();

    ASSERT_EQ(events.size(), 2);
    EXPECT_EQ(events[0].time, 90);
    EXPECT_EQ(events[0].id, 1);
    EXPECT_EQ(events[1].time, 165);
    EXPECT_EQ(events[1].id, 2);
    std::remove(filename.c_str());
}

TEST_F(ParserTest, GetEvents_InvalidFile) {
    std::string filename = createTxt("01:30 1 Event\nInvalid Line\n");
    std::ifstream file(filename);
    EXPECT_THROW(Parser::getEvents(file), std::runtime_error);
    file.close();
    std::remove(filename.c_str());
}
TEST_F(ParserTest, GetEvents_EmptyFile) {
    std::string filename = createTxt("");
    std::ifstream file(filename);
    std::vector<Event> events = Parser::getEvents(file);
    file.close();

    EXPECT_TRUE(events.empty());
    std::remove(filename.c_str());
}
TEST_F(ParserTest, MixedCases) {
    std::string filename = createTxt(
            "00:00 1 A\n"
            "23:59 4 E\n"
            "12:34 2 L 2\n"
            "01:30 0 I\n"
            "12:00 3 D\n"
    );
    std::ifstream file(filename);

    std::vector<Event> events;
    EXPECT_NO_THROW(events = Parser::getEvents(file));

    ASSERT_EQ(events.size(), 5);
    EXPECT_EQ(events[0].time, 0);
    EXPECT_EQ(events[0].id, 1);
    EXPECT_EQ(events[1].time, 1439);
    EXPECT_EQ(events[1].id, 4);
    EXPECT_EQ(events[2].time, 754);
    EXPECT_EQ(events[2].id, 2);
    EXPECT_EQ(events[3].time, 90);
    EXPECT_EQ(events[3].id, 0);

    file.close();
    std::remove(filename.c_str());
}