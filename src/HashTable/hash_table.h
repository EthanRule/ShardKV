#include <string>
#include <array>
#include "../Types/command.h"
#include "../Types/node.h"

typedef std::array<Node, 16384> table;
class HashTable {
private:
    table table;

public:
    // need to be able to listen to incoming events to execute commands
    void executeCommand(Command command);

    void set(std::string key, std::string value);

    std::string get(std::string key);

    void deleteItem(std::string key);

private:
    // TODO: Ensure this is 16 bits unsigned.
    ushort hash(std::string key);
};
