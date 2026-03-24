// key range of (or 0 – 16383)
#include "hash_table.h"

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


template<typename T>
T HashTable::Find(std::string key) {

    // iterator find(const K& key, size_t hash) const {
    //   size_t pos = H1(hash) % size_;
    //   while (true) {
    //     if (H2(hash) == ctrl_[pos] && key == slots[pos])
    //       return iterator_at(pos);
    //     if (ctrl_[pos] == kEmpty) return end();
    //     pos = (pos + 1) % size_;
    //   }
    // }

    // if get found key or didnt, notify core
    return "";
}

// size_t H1(size_t hash) { return hash >> 7; }
// ctrl_t H2(sizse_t hash) { return hash & 0x7F; }

void HashTable::Delete(std::string key) {

    // if keyval deleted, notify core
}


// which group to probe, should use last 57 bits.
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

