#ifndef SLOT_H_
#define SLOT_H_

#include <stdint.h>

template <typename T>
struct slot {
    uint64_t key;
    T val;
};

#endif // SLOT_H_