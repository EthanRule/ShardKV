#pragma once
#include "../../Types/result.h"
#include "../../Types/command.h"

class InputParser {
    public:
        std::pair<Result, Command> parseInput(std::string input);
        std::pair<Result, std::vector<std::string>> tokenize(std::string& input);
};
