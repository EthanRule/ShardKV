#include "core.h"

void Core::executeCommand(Command command) {
    undo.push_back(command);
    // push a notification with a command to hashtable
}

void Core::undoCommand() {

}

void Core::redoCommand() {

}