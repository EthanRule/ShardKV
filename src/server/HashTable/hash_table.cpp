// key range of (or 0 – 16383)
#include "hash_table.h"

void HashTable::ExecuteCommand(Command command) {
    switch (command.restAPI) {
        case RestAPI::SET:
            InsertItem(command.key, command.value);
            break;
        case RestAPI::GET:
            // auto res = GetItem(command.key);
            break;
        case RestAPI::DELETE:
            DeleteItem(command.key);
            break;
    }
}

template<typename T>
void HashTable::InsertItem(std::string key, T value) {
    // if a keyval got set, notify core
}

template<typename T>
T HashTable::GetItem(std::string key) {


    // if get found key or didnt, notify core
    return "";
}

void HashTable::DeleteItem(std::string key) {

    // if keyval deleted, notify core
}

// TODO: hash function that distributes entrophy across entire bit space and causes avalanch effect. https://abseil.io/docs/cpp/guides/hash
uint64_t HashTable::Hash(std::string key) {
    uint64_t res;
    // H1: 57 bits (normal hashvalue for lookup and insertions)
    //
    // H2: 7 bits (store metadata for this element. The H2 hash bits are stored seperatly within the metadata section of the table)



    return res;
}
