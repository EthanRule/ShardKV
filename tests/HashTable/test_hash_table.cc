#include "gtest/gtest.h"
#include "../../src/server/HashTable/hash_table.h"

// Note: functions like absl::Hash are not tested since they have their own tests in their library. Instead integration tests that combine
// this function will be used.

// Unit tests
TEST(HashTableTest, InsertKey) {
    HashTable table;

    // table.Insert("key", "value");

    // EXPECT_EQ(table.Find<std::string>("key"), "value");
}

TEST(HashTableTest, DeleteKey) {
    HashTable table;

}
