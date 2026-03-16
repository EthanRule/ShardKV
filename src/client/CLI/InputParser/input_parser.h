#ifndef INPUT_PARSER_H_
#define INPUT_PARSER_H_

#include "../../../Types/command.h"
#include <vector>

class InputParser {
    public:
        Command parseInput(std::string input);
        std::vector<std::string> tokenize(std::string& input);
};

#endif // INPUT_PARSER_H_