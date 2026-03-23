#ifndef GROUP_H_
#define GROUP_H_

#include "slot.h"
#include <array>

// NOTE: This is an operation, not an object. This needs to be moved into hash_table.h
// template <typename T>
struct group {
private: 
    size_t capacity = 16;

    // Needs to operate on a ctrl_t* and run simd instructions on a group of 16 slots

};

#endif // GROUP_H_
