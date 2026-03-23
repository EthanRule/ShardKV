#include "src/server/HashTable/hash_table.h"
#include <iostream>

int main() {
    HashTable table;
    table.Insert<std::string>("hello", "world");
    return 0;
}
