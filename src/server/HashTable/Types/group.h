#ifndef GROUP_H_
#define GROUP_H_

#include "slot.h"
#include <array>

template <typename T>
struct group {
    std::array<slot<T>, 8> vals;
};

#endif // GROUP_H_
