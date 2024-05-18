#include "Validator.h"
#include <gtest/gtest.h>

/*
ID 1. Клиент пришел
<время> 1 <имя клиента>
ID 2. Клиент сел за стол
<время> 2 <имя клиента> <номер стола>
ID 3. Клиент ожидает
<время> 3 <имя клиента>
ID 4. Клиент ушел
<время> 4 <имя клиента>
 */
TEST(ValidatorTest, Validate) {
    int N = 2;
    int timeOpen = 300;
    int timeClose = 600;
    int costHour = 10;
    std::vector<Event> events = {
            Event{301, 1, {"a"}},
            Event{302, 1, {"b"}},
            Event{303, 2, {"a", "1"}},
            Event{303, 2, {"a", "2"}}
    };
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, costHour, events), -1);
}

TEST(ValidatorTest, ValidateN) {
    int timeOpen = 300;
    int timeClose = 600;
    int costHour = 10;
    std::vector<Event> events = {
            Event{301, 1, {"a"}},
            Event{302, 1, {"b"}},
            Event{303, 2, {"a", "1"}},
            Event{303, 2, {"b", "2"}}
    };
    EXPECT_EQ(Validator::validate(-54, timeOpen, timeClose, costHour, events), 0);
}

TEST(ValidatorTest, ValidateTimeClose) {
    int N = 2;
    int timeOpen = 300;
    int costHour = 10;
    std::vector<Event> events = {
            Event{301, 1, {"a"}},
            Event{302, 1, {"b"}},
            Event{303, 2, {"a", "1"}},
            Event{303, 2, {"b", "2"}}
    };
    EXPECT_EQ(Validator::validate(N, timeOpen, -1, costHour, events), 1);
}

TEST(ValidatorTest, ValidateCostHour) {
    int N = 2;
    int timeOpen = 300;
    int timeClose = 600;
    std::vector<Event> events = {
            Event{301, 1, {"a"}},
            Event{302, 1, {"b"}},
            Event{303, 2, {"a", "1"}},
            Event{303, 2, {"b", "2"}}
    };
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, 0, events), 2);
}

TEST(ValidatorTest, ValidateTime) {
    int N = 2;
    int timeOpen = 300;
    int timeClose = 600;
    int costHour = 10;
    std::vector<Event> events = {Event{303, 1, {"g11"}},
                                 Event{301, 1, {"a"}}};
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, costHour, events), 4);
    timeOpen = 900; // 15:00
    timeClose = 120; // 2:00
    events = {Event{30, 1, {"g11"}}, //0:30
              Event{1200, 1, {"a"}}}; //20:00
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, costHour, events), 4);
}

TEST(ValidatorTest, ValidateId) {
    int N = 2;
    int timeOpen = 300;
    int timeClose = 600;
    int costHour = 10;
    std::vector<Event> events = {Event{301, 88, {"g11"}}};
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, costHour, events), 3);
}

TEST(ValidatorTest, ValidateName) {
    int N = 2;
    int timeOpen = 300;
    int timeClose = 600;
    int costHour = 10;
    std::vector<Event> events = {Event{301, 1, {"g11_-*"}}};
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, costHour, events), 3);

    EXPECT_TRUE(Validator::isValidName("valid_name"));
    EXPECT_TRUE(Validator::isValidName("valid-name"));
    EXPECT_TRUE(Validator::isValidName("name123"));
    EXPECT_FALSE(Validator::isValidName("InvalidName"));
    EXPECT_FALSE(Validator::isValidName("name!@#"));
    EXPECT_FALSE(Validator::isValidName("123!"));
}

TEST(ValidatorTest, ValidateBodySize) {
    int N = 2;
    int timeOpen = 300;
    int timeClose = 600;
    int costHour = 10;
    std::vector<Event> events;
    events = {Event{301, 1, {"g11", "1"}}};
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, costHour, events), 3);
    events = {Event{301, 2, {"g11"}}};
    EXPECT_EQ(Validator::validate(N, timeOpen, timeClose, costHour, events), 3);
}