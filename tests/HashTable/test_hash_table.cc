#include "gtest/gtest.h"
#include <string>
#include "../../src/server/HashTable/hash_table.h"

// NOTE: This file declares tests for HashTable member functions such as Insert, Find, and Delete.

// Unit tests
TEST(HashTableTest, InsertKey) {
    HashTable table;
    std::string key = "key";
    std::string value = "value";

    table.Insert(key, value);

    // EXPECT_EQ(table.Find<std::string>("key"), "value");
}
