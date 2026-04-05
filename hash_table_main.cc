#include "src/server/HashTable/hash_table.h"
#include <iostream>

int main() {
    HashTable table;
    table.Insert("hello", "world");
    table.Insert("hello2", "world");
    table.Insert("hello3", "world");
    table.Find("hello");
    return 0;
}
