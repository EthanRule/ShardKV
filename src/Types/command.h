#pragma once
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
