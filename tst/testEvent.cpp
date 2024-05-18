#include <gtest/gtest.h>
#include "Event.h"

TEST(EventTest, TimeToStr) {
    EXPECT_EQ(Event::timeToStr(0), "00:00");
    EXPECT_EQ(Event::timeToStr(60), "01:00");
    EXPECT_EQ(Event::timeToStr(5 * 60), "05:00");

    EXPECT_EQ(Event::timeToStr(65), "01:05");
    EXPECT_EQ(Event::timeToStr(125), "02:05");
    EXPECT_EQ(Event::timeToStr(1439), "23:59");
}

TEST(EventTest, ToStr) {
    Event event;
    event.time = 90; // 01:30
    event.id = 1;
    event.body = {"Event", "Body"};

    std::string expectedStr = "01:30 1 Event Body";

    EXPECT_EQ(event.toStr(), expectedStr);

    event.time = 10; // 00:10
    event.id = 2;
    event.body = {"client1", "1"};

    expectedStr = "00:10 2 client1 1";

    EXPECT_EQ(event.toStr(), expectedStr);
}