/* Credits to those who worked on Abseils swiss table and Redis. Go star their repos here:
 * https://github.com/abseil/abseil-cpp.git
 * https://github.com/redis/redis
 *
 * Also Jeff and Sanjay are the goats.
*/ 

/* This file outlines an adapted version of the Abseil Swiss Table. This is a simplified version 
 * in one way, and more complex in another. It supports strings as keys and values, and 
 * compiles with GCC to x84-64 on little endian machines. 
 *
 * Support for big endian machines and machines that cannot run SSE SIMD instuctions
 * is currently not supported.
 *
 */

/* NOTE: <+++ Common Terminology +++>
 * Slot: address that holds the value of an string pair on HashTable (not ctrl byte array).
 * Metadata: slang for a 7 bit ctrl byte that approximates the hash for a key.
 * Control array: array of metadata bytes e.g. full, empty, deleted, and end slot positions.
 * Group: 16 bytes in the control array.
 *
 */

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <string>
#include <array>
#include <stdint.h>
#include "../../Types/command.h"
#include "absl/hash/hash.h"
#include <iostream>

// Type for control bytes.
typedef int8_t ctrl_t;

// Full slot type.
typedef std::pair<std::string, std::string> slot_type;

// This is the main data structure in ShardKV.
class HashTable {
private:

    // Defines the capacity of the ctrl bytes array.
    static constexpr size_t capacity = 128;
    
    // NOTE: Special cases for control byte array.
    static constexpr ctrl_t kEmpty = -128;
    static constexpr ctrl_t kDeleted = -2;
    static constexpr ctrl_t kSentinel = -1;
    
    // Width to extend ctrl byte array by 1 group. A group is 16 slots.
    static constexpr size_t kWidth = 16;

    size_t growth_left;
    
    // NOTE: Control bytes: 0-127, Sentinel: 128, Clones: kWidth - 1.
    ctrl_t ctrl[capacity + 1 + kWidth - 1];

    slot_type slots[capacity];

public:

    // Constructor defines default values for HashTable.
    HashTable() {

        // Initialize the sentinel value at the end of the control byte array.
        ctrl[128] = kSentinel;
    }

    // Entry point to listen and execute commands.
    void ExecuteCommand(Command command);

    // Inserts a key into the table.
    void Insert(std::string key, std::string value);

    // Given a key, finds value in the table.
    std::string Find(std::string key);

    // Deletes key value pair in the table.
    void Delete(std::string key);

private:

    // NOTE: <<=== Find() Function Helpers ===>>

    // Determines which group (16 bytes) in the ctrl array to prob.
    size_t H1(uint64_t hash);

    // Detemines what metadata (7 bits) to probe for in each group.
    int8_t H2(uint64_t hash);
    
    /* Filters which bytes in our ctrl[] are worth checking the full 64 bit hash against.
     *
     * Given a start index of a group and a metadata byte, this func returns a 16 bit bitmask
     * that indicates which of the 16 bytes in the group equal the metadata byte and which don't.
     *
     * Example: Given a start index 16 and a byte to match.
     *
     * Byte to match: 00111010.
     * 
     * Returns: 0000010000000001.
     * 
     * This bitmask indicates that in ctrl[] at indices 21 and 31, both indices are equal to
     * the metadata byte we provided Match(). Afterwards we only need to check 21 and 31.
    */ 
    uint16_t Match(ctrl_t* start, ctrl_t byte);

    // Determines whether to probe further or stop. 
    uint16_t MatchEmpty(ctrl_t* start);

    // NOTE: <<=== Insert() Function Helpers ===>>




    // NOTE: <<=== Delete() Function Helpers ===>>




    // NOTE: <<=== General() Function Helpers ===>>
};

#endif // HASH_TABLE_H_
