#ifndef RESULT_H_
#define RESULT_H_

#include "status.h"
#include <string>

struct Result {
    Status status;
    std::string error;
};

#endif // RESULT_H_
