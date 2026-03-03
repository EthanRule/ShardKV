#include <iostream>
#include <string>
#include "../Types/command.h"

class CommandLineInterface {
    public:
        void run();

        Command parseInput(std::string input);

    private:
};
