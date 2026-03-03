#include "restAPI.h"
#include <vector>
#include <string>

struct Command {
    RestAPI restAPI;
    std::vector<std::string> arguments;
};
