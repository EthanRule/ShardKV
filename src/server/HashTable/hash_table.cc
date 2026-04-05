// key range of (or 0 – 16383)
#include "hash_table.h"
#include <immintrin.h> // https://clang.llvm.org/doxygen/immintrin_8h.html

void HashTable::ExecuteCommand(Command command) {
    switch (command.restAPI) {
        case RestAPI::SET:
            Insert(command.key, command.value);
            break;
        case RestAPI::GET:
            // auto res = GetItem(command.key);
            break;
        case RestAPI::DELETE:
            Delete(command.key);
            break;
    }
}

// Triangularly increasing linear probing insert.
void HashTable::Insert(std::string key, std::string value) {
    uint64_t hashValue = absl::Hash<std::string>{}(key);
    size_t slot = H1(hashValue);
    int8_t ctrl_byte = H2(hashValue);

    // Search the 16 ctrl bytes starting at `slot` to find an empty, then 
    // probe subsaquent groups with triangularly increasing jumps: https://en.wikipedia.org/wiki/Triangular_number
    size_t jumps = 1;
    size_t jump_size = 1;

    while(slot < capacity) {
        bool inserted = false;
        for (size_t i = slot; i < slot + 16; ++i) {
            if (ctrl[i] == kEmpty) {
                std::cout << "Inserting at: " << i << "\n";
                ctrl[i] = ctrl_byte;
                slots[i] = {key, value};
                inserted = true;
                break;
            }
        }

        if (inserted) break;
        
        std::cout << "Collision! jumping and trying again." << "\n";
        jump_size = (jumps * (jumps + 1)) / 2;
        jumps++;
        slot += 16 * jump_size;
    }
}

// Finds the key in the table.
// 
std::string HashTable::Find(std::string key) {
    uint64_t hash = absl::Hash<std::string>{}(key);
    size_t start = H1(hash);
    int8_t target_ctrl_byte = H2(hash);

    std::cout << "group from H1: " << start << "\n";
    std::cout << "target_ctrl_byte H2: " << target_ctrl_byte << "\n";
    bool sentinel_empty_found = false;

    while (sentinel_empty_found == false) {
        // Check if group has a empty or sentinel bit.
        ctrl_t* start_index = &ctrl[start];
        uint16_t empty_sentinel_bitmask = MatchEmpty(start_index);
        
        // Find the leftmost sentinel / empty set bit (this is our signal to stop searching).
        uint16_t index = __lzcnt16(empty_sentinel_bitmask);

        if (index == 16) { // No sentinels or empties found.
            index = -1;
        } else {
            sentinel_empty_found = true;
        }

        uint16_t mask = Match(start_index, target_ctrl_byte);
    
        // BMI1 x86-64 instruction
        // Purpose: Counts zeros from up until the occurance of the first set bit.
        uint16_t match_bit = __lzcnt16(targets_bitmask) - 16; 
    
        while (match_bit < 16) {
            // Check slot at index. // check if it equals the same hash or key? I think key.
            if (slot[match_bit].first == key) {
                return slot[match_bit].second;
            }

            /*
            * Brian Kernighan's Algorithm
            * Purpose: Flip the right most bit of a number n. are we sure we want to even do this?
            * Source: https://medium.com/@wizzywooz/brian-kernighans-algorithm-c65d796a7112
            *                          bin        dec
            *          n               00001000   8
            *          n + 1           00000111   7
            * // NOTE: n & (n - 1)     00000100   4
            */

            
            
            mask &= mask - 1;
            
            match_bit = __lzcnt16(mask) - 16;
        }
    

    //}

    

    return "";
}


void HashTable::Delete(std::string key) {
}

// Finds which group to probe, using last 57 bits.
size_t HashTable::H1(uint64_t hash) {
    return hash & (capacity - 1);
}

// 7 bit metadata for ctrl_t
int8_t HashTable::H2(uint64_t hash) {
    hash >>= 57;

    return (int8_t)hash;
}

// NOTE: Checks 16 control bytes to see if any match to "byte". This filters down to where the hash could be.
uint16_t HashTable::Match(size_t start, ctrl_t byte) {
    uint16_t res = 0;

    for (int i = 0; i < 16; ++i) {
        uint16_t mask = 0;

        if (ctrl[start] == byte) {
            mask = (1U << i);
        }

        res |= mask;
        start++;
    }

    return res;
}

// NOTE: 
// Returns mask that indicates whether an kEmpty or kSentinel exists.
uint16_t HashTable::MatchEmpty(ctrl_t* start) {
    uint16_t res = 0;

    for (int32_t i = 0; i < 16; ++i) {
        uint16_t mask= 0;
        if (*start == kEmpty || *start == kSentinel) {
            mask = (1U << i);
        }

        res |= mask;
        start++;
    }

    return res;
}

