#include "../CLI/command_line_interface.h"
#include "../HashTable/hash_table.h"
#include <vector>
#include "../Types/command.h"

class Core {
private:
    CommandLineInterface cli;
    HashTable hashTable;
    std::vector<Command> undo;
    std::vector<Command> redo;

public:
    void set(Command command);
    std::string get(Command command);
    void deleteKey(Command command);

private:

};
