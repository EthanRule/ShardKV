#pragma once
#include "status.h"
#include <string>

struct Result {
    Status status;
    std::string error;
};
