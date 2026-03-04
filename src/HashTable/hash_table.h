#include <string>
#include <array>
#include "../Types/node.h"

typedef std::array<Node, 16384> table;
class HashTable {
    table table;

    void set(std::string key, std::string value);
    std::string get(std::string key);
    void deleteItem(std::string key);
};
