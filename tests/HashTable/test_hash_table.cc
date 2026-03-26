#include "gtest/gtest.h"
#include "../../src/server/HashTable/hash_table.h"

// NOTE: This file declares tests for standard hash functions such as Insert, Find,
// and Delete.

// Unit tests
TEST(HashTableTest, InsertKey) {
    HashTable table;

    table.Insert<std::string>("key", "value");

    // EXPECT_EQ(table.Find<std::string>("key"), "value");
}

TEST(HashTableTest, DeleteKey) {
    HashTable table;

}
