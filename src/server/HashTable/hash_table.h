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

class HashTable {
private:
    template <typename T>
    static std::array<group<T>, 128> table; // TODO: figure out why this has to be static to work

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

    template <typename T>
    std::array<group<T>, 128> GetTable();
};

#endif // HASH_TABLE_H_
