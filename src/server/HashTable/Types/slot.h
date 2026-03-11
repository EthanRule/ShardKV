#include <stdint.h>

template <typename T>
struct slot {
    uint64_t key;
    T val;
};
