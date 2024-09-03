#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Define the Item structure
typedef struct Item {
    int key;
    int value;
    struct Item *next;  // For handling collisions using chaining
} Item;

// Define the HashTable structure
typedef struct HashTable {
    Item *table[TABLE_SIZE];
} HashTable;

// Hash function to compute index based on key
int hash_function(int key) {
    return key % TABLE_SIZE;
}

// Initialize the hash table
void init_hash_table(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// Add or update an item in the hash table
void set(HashTable *ht, int key, int value) {
    int index = hash_function(key);
    Item *current = ht->table[index];
    Item *prev = NULL;
    
    // Search for the key in the linked list
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        prev = current;
        current = current->next;
    }
    
    // Key not found, add a new item
    Item *new_item = (Item *)malloc(sizeof(Item));
    new_item->key = key;
    new_item->value = value;
    new_item->next = NULL;
    
    if (prev == NULL) {
        ht->table[index] = new_item;
    } else {
        prev->next = new_item;
    }
}

// Retrieve the value for a given key
int get(HashTable *ht, int key) {
    int index = hash_function(key);
    Item *current = ht->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    
    // Key not found
    fprintf(stderr, "Key not found\n");
    exit(EXIT_FAILURE);
}

// Remove an item with the given key from the hash table
void remove(HashTable *ht, int key) {
    int index = hash_function(key);
    Item *current = ht->table[index];
    Item *prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                ht->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    
    // Key not found
    fprintf(stderr, "Key not found\n");
    exit(EXIT_FAILURE);
}

// Example usage
int main() {
    HashTable ht;
    init_hash_table(&ht);
    
    set(&ht, 1, 100);
    set(&ht, 2, 200);
    
    printf("Value for key 1: %d\n", get(&ht, 1));
    printf("Value for key 2: %d\n", get(&ht, 2));
    
    remove(&ht, 1);
    // Uncommenting the following line will cause the program to exit with an error
    // printf("Value for key 1: %d\n", get(&ht, 1));
    
    return 0;
}
