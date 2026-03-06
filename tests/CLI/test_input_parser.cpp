#include <gtest/gtest.h>
#include "../../src/CLI/InputParser/input_parser.h"

// A simple test to make sure GTest is alive
TEST(InputParserTest, BasicSET) {
    Command expected = {RestAPI::SET, "apples", "5"};

    InputParser parser;
    Command command = parser.parseInput("SET apples 5");
    EXPECT_EQ(command, expected);
}

TEST(InputParserTest, BasicGET) {
    Command expected = {RestAPI::GET, "apples"};

    InputParser parser;
    Command command = parser.parseInput("GET cherries");
    EXPECT_EQ(command, expected);
}

TEST(InputParserTest, BasicDELETE) {
    Command expected = {RestAPI::DELETE, "apples"};

    InputParser parser;
    Command command = parser.parseInput("DELETE oranges");
    EXPECT_EQ(command, expected);
}

TEST(InputParserTest, BasicSet) {
    EXPECT_EQ(1, 1);
}



// You can eventually include your headers here:
// #include "CLI/InputParser/input_parser.hpp"
