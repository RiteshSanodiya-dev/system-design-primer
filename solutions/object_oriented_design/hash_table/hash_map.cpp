/*
 * Explanation:
 * 
 * Item Class:
 * - Contains `key` and `value` attributes.
 * - Includes a constructor to initialize these attributes.
 * 
 * HashTable Class:
 * - Constructor: Initializes the hash table with the given size.
 * - `hash_function` Method: Computes the index in the table based on the key.
 * - `set` Method: Adds a new item or updates an existing item in the hash table.
 * - `get` Method: Retrieves the value associated with the specified key.
 *   Throws `std::runtime_error` if the key is not found.
 * - `remove` Method: Removes the item associated with the specified key from the table.
 *   Throws `std::runtime_error` if the key is not found.
 * 
 * Implementation Details:
 * - Uses `std::vector` for the table to store the list of items.
 * - Uses `std::list` to handle collisions using chaining.
 * - Handles errors with `std::runtime_error` to indicate issues such as key not found.
 */

#include <vector>
#include <list>
#include <stdexcept> // for std::runtime_error

class Item {
public:
    int key;
    int value;

    Item(int k, int v) : key(k), value(v) {}
};

class HashTable {
private:
    int size;
    std::vector<std::list<Item>> table;

    int hash_function(int key) const {
        return key % size;
    }

public:
    HashTable(int s) : size(s), table(s) {}

    void set(int key, int value) {
        int hash_index = hash_function(key);
        for (auto& item : table[hash_index]) {
            if (item.key == key) {
                item.value = value;
                return;
            }
        }
        table[hash_index].emplace_back(key, value);
    }

    int get(int key) const {
        int hash_index = hash_function(key);
        for (const auto& item : table[hash_index]) {
            if (item.key == key) {
                return item.value;
            }
        }
        throw std::runtime_error("Key not found");
    }

    void remove(int key) {
        int hash_index = hash_function(key);
        auto& bucket = table[hash_index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                return;
            }
        }
        throw std::runtime_error("Key not found");
    }
};
