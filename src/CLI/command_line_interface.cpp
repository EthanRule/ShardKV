#include "command_line_interface.h"
#include "InputParser/input_parser.h"
#include <string>

void CommandLineInterface::run() {
    std::string input;
    InputParser parser;
    while(true) {
        std::cin >> input;
        std::cout << "You inputted: " << input << '\n';
        Command command = parser.parseInput(input);
        input.clear();
    }
}
