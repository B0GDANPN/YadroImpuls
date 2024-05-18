#include <gtest/gtest.h>
#include "EventHandler.h"

TEST(EventHandlerTest, test) {
    std::ostringstream oss;
    std::streambuf *originalBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    int N = 2;
    int timeOpen = 900; //15:00
    int timeClose = 120; //2:00
    int costHour = 10;
    std::vector<Event> events = {
            Event{840, 1, {"a"}},
            Event{900, 1, {"a"}},
            Event{900, 2, {"a", "1"}},
            Event{930, 2, {"a", "2"}},
            Event{1080, 1, {"b"}},
            Event{1080, 2, {"b", "1"}},
            Event{1110, 1, {"c"}},
            Event{1111, 1, {"d"}},
            Event{1118, 1, {"e"}},
            Event{1118, 3, {"d"}},
            Event{1140, 4, {"e"}},
            Event{1140, 4, {"d"}}
    };
    EventHandler::process(N, timeOpen, timeClose, costHour, events);
    std::cout.rdbuf(originalBuf);
    std::string expectedOutput = "15:00\n"
                                 "14:00 1 a\n"
                                 "14:00 13 NotOpenYet\n"
                                 "15:00 1 a\n"
                                 "15:00 2 a 1\n"
                                 "15:30 2 a 2\n"
                                 "18:00 1 b\n"
                                 "18:00 2 b 1\n"
                                 "18:30 1 c\n"
                                 "18:31 1 d\n"
                                 "18:38 1 e\n"
                                 "18:38 3 d\n"
                                 "18:38 11 d\n"
                                 "19:00 4 e\n"
                                 "19:00 4 d\n"
                                 "19:00 13 ClientUnknown\n"
                                 "02:00 11 a\n"
                                 "02:00 11 b\n"
                                 "02:00\n"
                                 "1 90 08:29\n"
                                 "2 110 10:29\n";
    EXPECT_EQ(oss.str(), expectedOutput);
}
