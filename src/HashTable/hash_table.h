#include <string>
#include <array>
#include "../Types/node.h"

typedef std::array<Node, 16384> table;
class HashTable {
private:
    table table;

public:
    void set(std::string key, std::string value);

    std::string get(std::string key);

    void deleteItem(std::string key);

private:
    // TODO: Ensure this is 16 bits unsigned.
    ushort hash(std::string key);
};
