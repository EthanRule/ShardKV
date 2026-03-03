#include "command_line_interface.h"
#include <string>

void CommandLineInterface::run() {
    std::string input;
    while(true) {
        std::cin >> input;
        std::cout << "You inputted: " << input << '\n';
        parseInput(input);
        input.clear();
    }
}

Command CommandLineInterface::parseInput(std::string input) {
    // Needs to return a "Command" datatype
}
