#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 // Define the size of the hash table

// Node structure for chaining (linked list)
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// Hash map structure containing an array of pointers to Node
typedef struct HashMap {
    Node* table[TABLE_SIZE];
} HashMap;

// Hash function
unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

// Create a new node
Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Initialize the hash map
void initializeHashMap(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
}

// Insert key-value pair into the hash map
void insert(HashMap* map, int key, int value) {
    unsigned int index = hash(key);
    Node* newNode = createNode(key, value);

    // If no collision
    if (map->table[index] == NULL) {
        map->table[index] = newNode;
    } else {
        // Collision: use chaining (linked list)
        Node* temp = map->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Search for a value by key in the hash map
int search(HashMap* map, int key) {
    unsigned int index = hash(key);
    Node* temp = map->table[index];

    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value; // Key found
        }
        temp = temp->next; // Traverse the linked list
    }

    return -1; // Key not found
}

// Delete a key-value pair from the hash map
void delete(HashMap* map, int key) {
    unsigned int index = hash(key);
    Node* temp = map->table[index];
    Node* prev = NULL;

    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key not found\n");
        return;
    }

    if (prev == NULL) {
        map->table[index] = temp->next; // Delete the head node
    } else {
        prev->next = temp->next; // Bypass the node to be deleted
    }

    free(temp);
    printf("Key deleted\n");
}

// Display the hash map
void display(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = map->table[i];
        while (temp != NULL) {
            printf("(%d, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Main function to demonstrate the hash map operations
int main() {
    HashMap map;
    initializeHashMap(&map);

    insert(&map, 1, 10);
    insert(&map, 2, 20);
    insert(&map, 12, 30); // Collision example

    printf("HashMap after insertions:\n");
    display(&map);

    int value = search(&map, 2);
    if (value != -1) {
        printf("Value for key 2: %d\n", value);
    } else {
        printf("Key not found\n");
    }

    delete(&map, 1);
    printf("HashMap after deletion:\n");
    display(&map);

    return 0;
}
