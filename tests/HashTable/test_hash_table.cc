// NOTE: This file declares tests for HashTable member functions such as Insert, Find, and Delete.

#include "gtest/gtest.h"
#include <string>
#include <array>
#include <unordered_set>
#include "../../src/server/HashTable/hash_table.h"

// Test inserting 1 key value pair.
TEST(HashTableTest, InsertKey) {
    HashTable table;
    std::string key = "key";
    std::string value = "value";

    table.Insert(key, value);
}

// Test inserting 5 key value pairs.
TEST(HashTableTest, InsertMultipleKeys) {
    HashTable table;
    std::array<std::pair<std::string, std::string>, 5> keys {{
    {"key1", "val1"}, {"key2", "val2"}, {"key3", "val3"}, {"key4", "val4"}, {"key5", "val5"}}};

    for (size_t i {}; i < keys.size(); ++i) {
        table.Insert(keys[i].first, keys[i].second);
    }
}

// Test inserting capacity (max slots in table) keys fill the entire table.
TEST(HashTableTest, InsertTableCapacityKeys_FullLoadFactor) {
    HashTable table;
    std::unordered_set<std::string> keys;
    for (size_t i = 1; i < table.GetCapacity(); ++i) {
        keys.insert({"key" + std::to_string(i)});
    }

    for (auto key : keys) {
        table.Insert(key, "val");
    }

    // Check if the table is full using it's load factor.
    EXPECT_EQ(table.GetLoadFactor(), 1.0f);

}

// Test inserting capacity + 1 for a runtime error.
TEST(HashTableTest, InsertTableCapacityPlusOneKeys) {
    HashTable table;
    std::unordered_set<std::string> keys;
    for (size_t i = 1; i < table.GetCapacity() + 1; ++i) {
        keys.insert({"key" + std::to_string(i)});
    }

    size_t i = 0;
    for (auto it = keys.begin(); it != keys.end() && i < table.GetCapacity() + 1; ++it, ++i) {
        if (i == table.GetCapacity()) {
            std::cout << "here1" << std::endl;
            EXPECT_THROW(table.Insert(*it, "val"), std::runtime_error);
            break;
        }

        std::cout << "here2" << std::endl;
        table.Insert(*it, "val");
    }
}

// Test inserting capacity (max slots in table) keys are all found unique.
TEST(HashTableTest, InsertTableCapacityKeys_AllUniqueKeysExist) {
    HashTable table;
    std::unordered_set<std::string> keys;
    for (size_t i = 1; i < table.GetCapacity(); ++i) {
        keys.insert({"key" + std::to_string(i)});
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

// Test find 1 key value pair.
TEST(HashTableTest, FindKey) {
    HashTable table;
    std::string key = "key";
    std::string value = "value";

    table.Insert(key, value);

    EXPECT_EQ(table.Find(key), value);
}

// Test find multiple pair.
TEST(HashTableTest, FindMultiplePairs) {
    HashTable table;
    std::array<std::pair<std::string, std::string>, 5> keys {{
    {"key1", "val1"}, {"key2", "val2"}, {"key3", "val3"}, {"key4", "val4"}, {"key5", "val5"}}};

    for (size_t i {}; i < keys.size(); ++i) {
        table.Insert(keys[i].first, keys[i].second);
    }

    EXPECT_EQ(table.Find("key1"), "val1");
    EXPECT_EQ(table.Find("key2"), "val2");
    EXPECT_EQ(table.Find("key3"), "val3");
    EXPECT_EQ(table.Find("key4"), "val4");
    EXPECT_EQ(table.Find("key5"), "val5");
}

