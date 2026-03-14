#include <gtest/gtest.h>
#include "../../src/client/CLI/InputParser/input_parser.h"

TEST(InputParserTest, BasicSET) {
    Command expected = {RestAPI::SET, "apples", "5"};

    InputParser parser;
    Command command = parser.parseInput("SET apples 5");
    EXPECT_EQ(command, expected);
}

TEST(InputParserTest, BasicGET) {
    Command expected = {RestAPI::GET, "cherries"};

    InputParser parser;
    Command command = parser.parseInput("GET cherries");
    EXPECT_EQ(command, expected);
}

TEST(InputParserTest, BasicDELETE) {
    Command expected = {RestAPI::DELETE, "oranges"};

    InputParser parser;
    Command command = parser.parseInput("DELETE oranges");
    EXPECT_EQ(command, expected);
}
