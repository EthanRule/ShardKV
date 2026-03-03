#include "command_line_interface.h"
#include "InputParser/input_parser.h"
#include <string>

void CommandLineInterface::run() {
    std::string input;
    InputParser parser;
    while(true) {
        std::getline(std::cin, input);
        std::pair<Result, Command> command = parser.parseInput(input);
        if (command.first.status == Status::ERROR) {
            std::cout << command.first.error << '\n';
            input.clear();
            continue;
        }

        input.clear();
    }
}
