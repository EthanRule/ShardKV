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
__attribute__((target("bmi")))
std::string HashTable::Find(std::string key) {
    uint64_t hash = absl::Hash<std::string>{}(key);
    size_t start = H1(hash);
    int8_t target_ctrl_byte = H2(hash);
    std::cout << "target_ctrl_byte: " << target_ctrl_byte << std::endl;
    bool sentinel_empty_found = false;

    int iteration = 0;

    while (sentinel_empty_found == false) {
        std::cout << "iteration: " << ++iteration << "\n";
        // Check if group has a empty or sentinel bit.
        ctrl_t* start_index = &ctrl[start];

        uint16_t empty_sentinel_bitmask = MatchEmpty(start_index);
        
        // Find the leftmost sentinel / empty set bit (this is our signal to stop searching).
        uint16_t index = __tzcnt_u16(empty_sentinel_bitmask);

        if (index == 16) { // No sentinels or empties found.
            index = -1;
        } else {
            sentinel_empty_found = true;
            LogBitmask(empty_sentinel_bitmask);
            std::cout << "Found sentinel / empty" << "\n";
        }

        uint16_t targets_bitmask = Match(start_index, target_ctrl_byte);
        std::cout << "match_bit bitmask: ";
        LogBitmask(targets_bitmask);
        std::cout << "houashduioashuiodashuiodhasuisdhuiodhuiashdere" << "\n";
    
        // BMI1 x86-64 instruction
        // _tzcnt_u16(): Counts zeros from lsb up until the occurance of the first set bit.
        // Finds the index of: 0010001000000000
        //                           ^
        
        uint16_t match_bit = __tzcnt_u16(targets_bitmask); 
        std::cout << "match_bit: " << match_bit << "\n";
        
        while (match_bit < 16) {
            // Check slot at index. Remember. Slots is the actual array of Key Value pairs.
            // TODO: start here. Need to determine why key is not being found.
            LogSlots();
            std::cout << "slots[match_bit + start].first: " << slots[match_bit + start].first << "\n";
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


