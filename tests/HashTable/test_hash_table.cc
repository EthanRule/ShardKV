// NOTE: This file declares tests for HashTable member functions such as Insert, Find, and Delete.

#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <array>
#include <unordered_set>
#include "../../src/server/HashTable/hash_table.h"

// Test inserting 1 key value pair.
TEST(HashTableTest, InsertKey) {
    HashTable table;
    std::string key = "key";
    std::string value = "value";

    table.Insert(key, value);
    
    // EXPECT_EQ(table.Find<std::string>("key"), "value");
}

// Test inserting 5 key value pairs.
TEST(HashTableTest, InsertMultipleKeys) {
    HashTable table;
    std::array<std::pair<std::string, std::string>, 5> keys {{
    {"key1", "val1"}, {"key2", "val2"}, {"key3", "val3"}, {"key4", "val4"}, {"key5", "val5"}}};

    for (size_t i {}; i < keys.size(); ++i) {
        table.Insert(keys[i].first, keys[i].second);
    }

    // EXPECT_EQ(table.Find<std::string>("key"), "value");
}

// Test inserting capacity (max slots in table) keys fill the entire table.
TEST(HashTableTest, InsertTableCapacityKeys_FullLoadFactor) {
    HashTable table;
    std::unordered_set<std::string> keys;
    for (size_t i {}; i < keys.size(); ++i) {
        keys.insert({"key" + i});
    }

    for (auto key : keys) {
        table.Insert(key, "val");
    }

    // Check if the table is full using it's load factor.
    EXPECT_EQ(table.GetLoadFactor(), 1.0f);

}

// Test inserting capacity (max slots in table) keys are all found unique.
TEST(HashTableTest, InsertTableCapacityKeys_AllUniqueKeysExist) {
    HashTable table;
    std::unordered_set<std::string> keys;
    for (size_t i {}; i < keys.size(); ++i) {
        keys.insert({"key" + i});
    }

    for (auto key : keys) {
        table.Insert(key, "val");
    }

    // Check if the table contains each unique pair<key, val>.
    const slot_type* table_start = table.GetHashTablePairs();

    for (size_t i {}; i < table.GetCapacity(); ++i) {
        keys.erase(table_start[i].first);
    }

    EXPECT_EQ(keys.size(), 0);
}

