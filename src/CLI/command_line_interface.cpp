#include "command_line_interface.h"
#include <string>

void CommandLineInterface::run() {
    std::string input;
    while(true) {
        std::cin >> input;
        std::cout << "You inputted: " << input << '\n';
        input.clear();
    }
}
