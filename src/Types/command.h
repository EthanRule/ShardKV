#ifndef COMMAND_H_
#define COMMAND_H_

#include "rest_API.h"
#include <string>

struct Command {
    RestAPI restAPI;
    std::string key;
    std::string value;

    bool operator==(const Command& other) const {
        return restAPI == other.restAPI && key == other.key && value == other.value;
    }
};

#endif // COMMAND_H_