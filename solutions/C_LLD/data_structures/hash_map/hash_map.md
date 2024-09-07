## Hash Map Design Using Chaining

### Explanation:

#### Hash Function:
- The key modulo the table size is used to generate the index.

#### Chaining:
- A linked list is used at each index of the hash table to resolve collisions. Each index of the hash table contains a pointer to the head of a linked list. In case of collisions, nodes are added to this list.

#### Insert:
- The `insert` function inserts a key-value pair into the hash map. If a collision occurs at a particular index, the new node is added to the end of the linked list at that index.

#### Search:
- The `search` function traverses the linked list at the computed index to find the key. It returns the corresponding value if the key is found, otherwise, it returns `-1` to indicate the key was not found.

#### Delete:
- The `delete` function removes a key-value pair from the hash map. It handles cases where the node to be deleted is at the head of the linked list or in the middle.

#### Display:
- The `display` function prints the current state of the hash map, showing each key-value pair stored in the hash map along with its index in the table.

### Key Concepts:

- **Hashing**: Used to compute the index for each key by taking the modulo of the key with the table size.
- **Chaining**: Used to handle collisions by storing multiple key-value pairs in a linked list at the same index.
- **Dynamic Memory**: Used to allocate memory for the linked list nodes as they are inserted into the hash map.

This implementation of a hash map can be extended for more advanced features such as:
- Dynamic resizing of the hash map.
- Using open addressing techniques like linear probing or double hashing instead of chaining for collision resolution.
