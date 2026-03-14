// key range of (or 0 – 16383)
#include "absl/hash/hash.h"
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
void HashTable::Insert(std::string key, T value) {
    // if a keyval got set, notify core
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

// TODO: hash function that distributes entrophy across entire bit space and causes avalanch effect. https://abseil.io/docs/cpp/guides/hash
uint64_t HashTable::Hash(std::string key) {
    uint64_t res;
    // H1: 57 bits (normal hashvalue for lookup and insertions)
    //
    // H2: 7 bits + 1 control bit (store metadata for this element. The H2 hash bits are stored seperatly within the metadata section of the table)

    // Empty 10000000
    // Full 0 0x43
    // Deleted 11111110


    return res;
}
