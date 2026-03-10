// Using the hash slot algorithm we can set this project up for multiple clients and sharding.
// key range of (or 0 – 16383)
#include "hash_table.h"

void HashTable::executeCommand(Command command) {
    switch (command.restAPI) {
        case RestAPI::SET:
            set(command.key, command.value);
            break;
        case RestAPI::GET:
            get(command.key);
            break;
        case RestAPI::DELETE:
            deleteItem(command.key);
            break;
    }
}

void HashTable::set(std::string key, std::string value) {
    // if a keyval got set, notify core
}

std::string HashTable::get(std::string key) {


    // if get found key or didnt, notify core
    return "";
}

void HashTable::deleteItem(std::string key) {

    // if keyval deleted, notify core
}

ushort HashTable::hash(std::string key) {
   uint16_t res; 
   
   return res;
}
