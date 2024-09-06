#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 5  // Cache capacity

// Node for the doubly linked list
typedef struct Node {
    int key;
    int value;
    struct Node *prev, *next;
} Node;

// Hash table entry
typedef struct HashEntry {
    Node *node;
} HashEntry;

// LRU Cache structure
typedef struct LRUCache {
    int capacity;
    int size;
    Node *head, *tail;
    HashEntry *hashTable[CAPACITY];
} LRUCache;

// Create a new doubly linked list node
Node* createNode(int key, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Initialize the LRU Cache
LRUCache* initCache(int capacity) {
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    memset(cache->hashTable, 0, sizeof(cache->hashTable));
    return cache;
}

// Move a node to the front (head) of the list
void moveToHead(LRUCache *cache, Node *node) {
    if (cache->head == node) return;  // It's already the head

    // Remove the node from its current position
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    // If it was the tail, update the tail
    if (node == cache->tail) cache->tail = node->prev;

    // Move the node to the front (head)
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;

    // If there's no tail (only one element), update it
    if (!cache->tail) cache->tail = node;
}

// Remove the tail (least recently used item)
void removeTail(LRUCache *cache) {
    if (!cache->tail) return;

    Node *oldTail = cache->tail;

    // Update the tail pointer
    cache->tail = oldTail->prev;
    if (cache->tail) cache->tail->next = NULL;

    // Remove from hash table
    cache->hashTable[oldTail->key % CAPACITY] = NULL;

    free(oldTail);
    cache->size--;
}

// Insert a new node at the front (head) of the list
void insertAtHead(LRUCache *cache, Node *node) {
    node->next = cache->head;
    node->prev = NULL;

    if (cache->head) cache->head->prev = node;
    cache->head = node;

    if (!cache->tail) cache->tail = node;
}

// Get a value from the cache
int get(LRUCache *cache, int key) {
    int hashIndex = key % CAPACITY;
    HashEntry *entry = cache->hashTable[hashIndex];

    if (entry && entry->node && entry->node->key == key) {
        // Move the accessed node to the front (most recently used)
        moveToHead(cache, entry->node);
        return entry->node->value;
    }

    return -1;  // Key not found
}

// Put a key-value pair into the cache
void put(LRUCache *cache, int key, int value) {
    int hashIndex = key % CAPACITY;
    HashEntry *entry = cache->hashTable[hashIndex];

    if (entry && entry->node && entry->node->key == key) {
        // Update the value of the existing node
        entry->node->value = value;
        // Move the node to the front (most recently used)
        moveToHead(cache, entry->node);
    } else {
        // If the cache is full, remove the least recently used item (tail)
        if (cache->size == cache->capacity) {
            removeTail(cache);
        }

        // Create a new node
        Node *newNode = createNode(key, value);

        // Insert the new node at the front (head)
        insertAtHead(cache, newNode);

        // Add to the hash table
        cache->hashTable[hashIndex] = (HashEntry *)malloc(sizeof(HashEntry));
        cache->hashTable[hashIndex]->node = newNode;

        cache->size++;
    }
}

// Print the contents of the cache
void printCache(LRUCache *cache) {
    Node *current = cache->head;
    printf("Cache: ");
    while (current) {
        printf("(%d, %d) ", current->key, current->value);
        current = current->next;
    }
    printf("\n");
}

// Free the entire cache
void freeCache(LRUCache *cache) {
    Node *current = cache->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(cache);
}

// Main function to demonstrate the LRU Cache
int main() {
    LRUCache *cache = initCache(3);

    put(cache, 1, 100);
    put(cache, 2, 200);
    put(cache, 3, 300);
    printCache(cache);

    get(cache, 2); // Access key 2 (200 should be moved to the front)
    printCache(cache);

    put(cache, 4, 400); // This should remove key 1 (least recently used)
    printCache(cache);

    get(cache, 1); // Access key 1 (which is no longer in the cache)
    printCache(cache);

    freeCache(cache);
    return 0;
}
