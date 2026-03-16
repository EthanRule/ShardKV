#ifndef COMMAND_LINE_INTERFACE_H_
#define COMMAND_LINE_INTERFACE_H_

#pragma once
#include "../../Types/observer.h"

class CommandLineInterface {
    public:
        // this probably needs to subscribe to Core on construct to receive updates.
        // this also prob needs to be a subject to notify Core for new commands.
        void run();
};

#endif // COMMAND_LINE_INTERFACE_H_
