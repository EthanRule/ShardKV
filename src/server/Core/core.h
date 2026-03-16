#ifndef CORE_H_
#define CORE_H_

#include "../HashTable/hash_table.h"
#include <vector>
#include "../../Types/command.h"
#include "../../Types/observer.h"

class Core {
private:
    // this probably needs to handle an asynchronous pool of threads to accept requests from multiple clients.
    // the observer patten needs to go back and fourth between this core class and hashmap. the core class might need to attach an ip address to each command too.
    // this needs to ovserve and recive notifications from hashtable, then route them to cli

    HashTable hashTable;
    std::vector<Command> undo;
    std::vector<Command> redo;

public:
    void executeCommand(Command command);
    void undoCommand();
    void redoCommand();

private:

};

#endif // CORE_H_
