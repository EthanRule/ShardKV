// Inspired by Googles swiss table.
#include <string>
#include <array>
#include <stdint.h>
#include "../../Types/command.h"
#include "../../Types/node.h"

typedef std::array<Node, 16384> table;
class HashTable {
private:
    table table;

public:
    // need to be able to listen to incoming events to execute commands
    void ExecuteCommand(Command command);

    template<typename T>
    void InsertItem(std::string key, T value);

    template<typename T>
    T GetItem(std::string key);

    void DeleteItem(std::string key);

private:
    uint64_t Hash(std::string key);
};
