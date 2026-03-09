#pragma once
#include "../../../Types/command.h"
#include <vector>

class InputParser {
    public:
        Command parseInput(std::string input);
        std::vector<std::string> tokenize(std::string& input);
};
