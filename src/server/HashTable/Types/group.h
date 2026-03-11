#include "slot.h"
#include <array>

template <typename T>
struct group {
    std::array<slot<T>, 8> vals;
};
