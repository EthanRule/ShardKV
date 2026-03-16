// Inspired by Googles swiss table.
#include <string>
#include <array>
#include <stdint.h>
#include "../../Types/command.h"
// #include "../../Types/node.h"
#include "Types/group.h"

class HashTable {
private:
    template <typename T>
    static std::array<group<T>, 128> table; // TODO: figure out why this has to be static to work

public:
    // need to be able to listen to incoming events to execute commands
    void ExecuteCommand(Command command);

    template<typename T>
    void Insert(std::string key, T value);

    template<typename T>
    T Find(std::string key);

    void Delete(std::string key);

    template <typename T>
    std::array<group<T>, 128> GetTable();
};
