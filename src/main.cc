#include "client/CLI/command_line_interface.h"
#include "server/Core/core.h"
using namespace std;

int main(void) {
    // cout << "Hello World." << endl;
    // CommandLineInterface commandLineInterface;
    // commandLineInterface.run();
    Core core;
    core.run();
    return 0;
}
