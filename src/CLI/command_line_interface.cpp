#include "InputParser/input_parser.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include "command_line_interface.h"

void CommandLineInterface::run() {
    std::string input;
    InputParser parser;
    while(true) {
        std::getline(std::cin, input);
        try {
            Command command = parser.parseInput(input);
            // do work


        }
        catch (std::runtime_error e) {
            std::cerr << e.what() << '\n';
            continue;
        }
        input.clear();
    }
}
