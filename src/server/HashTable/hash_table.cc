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


template <typename T>
std::array<group<T>, 128> HashTable::GetTable() {
    return table<T>;
}
