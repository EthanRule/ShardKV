// Inspired by Googles swiss table.

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <string>
#include <array>
#include <stdint.h>
#include "../../Types/command.h"
// #include "../../Types/node.h"
#include "Types/group.h"
#include "absl/hash/hash.h"
#include <iostream>

//     // Sampling handler. This field isn't present when the sampling is
//     // disabled or this allocation hasn't been selected for sampling.
//     HashtablezInfoHandle infoz_;
//     // The number of elements we can insert before growing the capacity.
//     size_t growth_left;
//     // Control bytes for the "real" slots.
//     ctrl_t ctrl[capacity];
//     // Always `ctrl_t::kSentinel`. This is used by iterators to find when to
//     // stop and serves no other purpose.
//     ctrl_t sentinel;
//     // A copy of the first `kWidth - 1` elements of `ctrl`. This is used so
//     // that if a probe sequence picks a value near the end of `ctrl`,
//     // `Group` will have valid control bytes to look at.
//     ctrl_t clones[kWidth - 1];
//     // The actual slot data.
//     slot_type slots[capacity];

typedef int8_t ctrl_t;
// NOTE: Uses int8_t for 3 types of values.
// low 7 bits of H2 hash: 0 - 127,
// kEmpty: -128,
// kDeleted = -2;
// kSentinel: -1;
// Notice how all special cases have their first bit set to 1. TODO: figure out why that makes SIMD
// instructions work.


typedef std::pair<std::string, std::string> slot_type; // TODO: make this generic in the future.

class HashTable {
private:
    static constexpr size_t capacity = 128; // TODO: make this set at runtime for rehashing. Use multiples of 16. 
    
    static constexpr ctrl_t kEmpty = -128;
    static constexpr ctrl_t kDeleted = -2;
    static constexpr ctrl_t kSentinel = -1;

    static constexpr size_t kWidth = 16;

    size_t growth_left;

    ctrl_t ctrl[capacity];

    // NOTE: the sentinel is used for letting iterators over the ctrl know that it has ended.
    ctrl_t sentinel;

    // NOTE: the clones are used for ensuring group loads starting near the end of ctrl
    // have the bytes to run a full 16 byte SIMD comparrison?
    ctrl_t clones[kWidth - 1];

    slot_type slots[capacity];

public:
    // need to be able to listen to incoming events to execute commands
    void ExecuteCommand(Command command);

    template<typename T>
    void Insert(std::string key, T value) {
        // if a keyval got set, notify core
        //
        // 64 bits of result from absl:Hash. First 57 are the Hash Code and the last 7 are metadata.
        uint64_t hashValue = absl::Hash<std::string>{}(key);

        std::cout << "hashValue: " << hashValue << "\n";
    }

    template<typename T>
    T Find(std::string key);

    void Delete(std::string key);

    // template <typename T>
};

#endif // HASH_TABLE_H_
