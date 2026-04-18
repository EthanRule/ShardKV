#include "hash_table.h"

void HashTable::ExecuteCommand(Command command) {
    switch (command.restAPI) {
        case RestAPI::SET:
            Insert(command.key, command.value);
            break;
        case RestAPI::GET:
            // std::string res = Find(command.key);
            break;
        case RestAPI::DELETE:
            Delete(command.key);
            break;
    }
}

/* 
The `Insert()` function utilizes a Triangularly increasing probing. This ensures
that every group in the table gets visited eventually.

* Why not Quadratic or Linear probing?
Quadratic probing does not guarentee every group is visited.
Linear probing risks frequent O(n) probing of every group.

Trangular probing can be explained as follows:

    Jump Size = n * (n + 1) / 2.

    With the Jump Size increase between every probe, a low-load-factor table finds 
    new `kEmpty` fields quicker, and in the worst case on a table where the 
    capacity is a power 2^n it will wrap around and visit all groups.

In this example we are starting from group 1 (0-15), though in the code the H1 hash could start 
us off at in the middle of a random group between 0 and capcity - 1.

Starting from `n == 0`, we probe the start group for an `kEmpty` slot.
If no `kEmpty` slot is found, `n` (or `jumps`) += 1.

Visited Groups: *
Current Group: ^
// is this even accurate? it seems to jump by n not by jump_size
                  groups                                `n`       `Jump Size`
-----------------------------------------------------------------------------
 *
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        0             0
 ^
-----------------------------------------------------------------------------
 *     *
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        1             1
       ^ 
-----------------------------------------------------------------------------
 *     *           * 
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        2             3
                   ^
-----------------------------------------------------------------------------
 *     *           *                 *
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        3             6
                                     ^
-----------------------------------------------------------------------------
 *     *     *     *                 *
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        4             10
             ^ 
-----------------------------------------------------------------------------
 *     *     *     *                 *       *
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        5             15
                                             ^ 
-----------------------------------------------------------------------------
 *     *     *     *           *     *       *
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        6             21
                               ^
-----------------------------------------------------------------------------
 *     *     *     *     *     *     *       *
0-15 16-31 32-47 48-63 64-79 80-95 96-111 112-127        7             28
                         ^

Source: https://en.wikipedia.org/wiki/Triangular_number
*/

void HashTable::Insert(std::string key, std::string value) {
    uint64_t hashValue = absl::Hash<std::string>{}(key);
    size_t slot = H1(hashValue); // need to log the table before hand, the intitial slot, then the jumps and see why its not inserting at the correct position.
    size_t initial_slot = slot;
    std::cout << "Initial slot: " << initial_slot << std::endl;
    // LogSlots();
    int8_t ctrl_byte = H2(hashValue);

    bool inserted = false;
    size_t max_jumps = capacity / kWidth;
    size_t jumps = 0;

    while(jumps < max_jumps) {
        //std::cout << "jumping: " << jumps << " times, and checking 16 slots from: " << slot << std::endl;
        std::cout << "Group range: " << slot << " - " << slot + 15 << std::endl;
        for (size_t i = slot; i < slot + 16; ++i) {
            if (ctrl[i] == kEmpty) {

                // Check if its a clone.
                if (i > capacity) {
                    ctrl[i - capacity - 1] = ctrl_byte;
                    ctrl[i] = ctrl_byte;
                    slots[i - capacity - 1] = {key, value};
                } else {
                    ctrl[i] = ctrl_byte;
                    slots[i] = {key, value};
                }

                inserted = true;
                growth_left--;
                break;
            } else {
                //std::cout << "slot: " << i << " is not kEmpty: " << ctrl[i] << std::endl;
            }
        }

        if (inserted) break;

        jumps++;
        size_t jump_size = (jumps * (jumps + 1)) / 2;
        //std::cout << "\nNew jump_size: " << jump_size << std::endl;
        slot += (16 * jump_size);
        //std::cout << "New slot: " << slot << std::endl;
        if (slot > capacity) { // If we are in the clones group, wrap around.
            //
            slot %= capacity;
            //std::cout << "slot after mod: " << slot << std::endl;
        }
    }

    if (!inserted && GetLoadFactor() == 1.0f) {
        std::cout << "growth_left: " << growth_left << std::endl;
        throw std::runtime_error("Failed to insert. Table full.");
    } else if (!inserted && GetLoadFactor() < 1.0f) {
        std::cout << "growth_left: " << growth_left << std::endl;
        throw std::runtime_error("Failed to insert. Table less than full.");
    } else if (!inserted && GetLoadFactor() > 1.0f) {
        std::cout << "growth_left: " << growth_left << std::endl;
        throw std::runtime_error("Failed to insert. Table more than full.");
    }
}

// Finds the key in the table.
__attribute__((target("bmi")))
std::string HashTable::Find(std::string key) {
    uint64_t hash = absl::Hash<std::string>{}(key);
    size_t start = H1(hash);
    int8_t target_ctrl_byte = H2(hash);
    bool sentinel_empty_found = false;

    while (sentinel_empty_found == false) {
        // Check if group has a empty or sentinel bit.
        ctrl_t* start_index = &ctrl[start];
        uint16_t empty_sentinel_bitmask = MatchEmpty(start_index);
        
        // Find the least significant sentinel or empty set bit.
        int32_t stop_index = __tzcnt_u16(empty_sentinel_bitmask);

        if (stop_index == 16) { // No sentinels or empties found.
            stop_index = -1;
        } else {
            sentinel_empty_found = true;
        }

        uint16_t targets_bitmask = Match(start_index, target_ctrl_byte);
    
        // BMI1 x86-64 instruction
        // _tzcnt_u16(): Counts zeros from lsb up until the occurance of the first set bit.
        // Finds the index of: 0010001000000000
        //                           ^
        uint16_t match_bit = __tzcnt_u16(targets_bitmask); 
        
        // Don't go past 15 and dont look at match_bits past a `kSentinel` or `kEmpty`.
        while (match_bit < 16 && !(stop_index >= 0 && match_bit > stop_index)) {
            // Check slot at index. Remember, `slots` is the actual array of key value pairs.
            if (slots[match_bit + start].first == key) {
                return slots[match_bit + start].second;
            }

            // Flip the least significant set bit. e.g. 0010001000000000 -> 0010000000000000
            //                                                ^                   ^
            targets_bitmask &= (targets_bitmask - 1);

            // Find the next match_bit index.      e.g. 0010000000000000 -> 0010000000000000
            //                                                ^               ^
            match_bit = __tzcnt_u16(targets_bitmask);
        }

        // Increment start to the next group.
        start += 16;
    }

    throw std::runtime_error("HashTable: key : `" + key + "` does not exist.");
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
uint16_t HashTable::Match(ctrl_t* start, ctrl_t byte) {
    uint16_t res = 0;

    for (int i = 0; i < 16; ++i) {
        uint16_t mask = 0;

        if (*start == byte) {
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

// NOTE: <<=== Debug Helpers ===>>
void HashTable::LogBitmask(uint16_t bitmask) {
    std::bitset<16> bits(bitmask);
    std::cout << "Bitmask: " << bits << std::endl;
}

void HashTable::LogSlots() {
    std::cout << "Slots: " << "\n";
    for (size_t i = 0; i < capacity; ++i) {
        std::cout << "slot " << i << "\n";
        std::cout << "(key: `" << slots[i].first << "` value: `" << slots[i].second << "`)\n";
    }
}


