#pragma once
#include "rest_API.h"
#include <vector>
#include <string>

struct Command {
    RestAPI restAPI;
    std::string key;
    std::string value;
};
