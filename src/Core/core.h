#include "../HashTable/hash_table.h"
#include <vector>
#include "../Types/command.h"
#include "../Types/observer.h"

class Core {
private:
    // this needs to be an observer that observes the commandlineinterface for new commands.
    // this needs to ovserve and recive notifications from hashtable, then bubble them up to cli
    // this needs to propogate commands from cli down to hash table in the executeCommand() function

    HashTable hashTable;
    std::vector<Command> undo;
    std::vector<Command> redo;

public:
    void executeCommand(Command command);
    void undoCommand();
    void redoCommand();

private:

};
