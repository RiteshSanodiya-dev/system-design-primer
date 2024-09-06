# LRU Cache Implementation - Explanation

## Core Components:

1. **Doubly Linked List**:
   - **Purpose**: Maintain the order of usage. The most recently used item is at the head of the list, and the least recently used (LRU) item is at the tail.
   - **Operations**:
     - When an item is accessed or added, it is moved to the head of the list.
     - When the cache exceeds capacity, the tail (LRU item) is removed.
   
2. **Hash Table**:
   - **Purpose**: Provides O(1) lookup for the keys. Each key maps to a node in the doubly linked list.
   - **Operations**:
     - When we `get` or `put` a key, we use the hash table to find the corresponding node in the list.

## LRU Cache Operations:
1. **Get**: If the key is in the cache (hash table), move its corresponding node to the head of the linked list (making it the most recently used). Return its value. If the key is not found, return `-1`.
2. **Put**: Insert a new key-value pair. If the key is already present, update the value and move the node to the head. If the cache is full, remove the node at the tail (least recently used) before inserting the new node at the head.

## Diagram Representation:

Below is a simplified diagram to explain how these structures interact:

### Initial State:
Capacity: 3

Cache (Doubly Linked List): Empty
Hash Table: Empty

### Step 1: `put(1, 100)` (Insert key 1 with value 100)
- The cache has space, so we insert the new key-value pair as a node.
- The node is inserted at the head of the doubly linked list.
- The hash table maps key `1` to this new node.

Doubly Linked List (Cache Order): [1: 100]

Hash Table: 1 -> Node(1: 100)


### Step 2: `put(2, 200)` (Insert key 2 with value 200)
- The cache has space, so insert key `2` with value `200` at the head.
- Key `1` becomes less recently used (moves down in the list).

Doubly Linked List (Cache Order): [2: 200] <-> [1: 100]

Hash Table: 1 -> Node(1: 100) 2 -> Node(2: 200)


### Step 3: `put(3, 300)` (Insert key 3 with value 300)
- The cache still has space, so insert key `3` at the head.
- Key `1` becomes the least recently used.

Doubly Linked List (Cache Order): [3: 300] <-> [2: 200] <-> [1: 100]

Hash Table: 1 -> Node(1: 100) 2 -> Node(2: 200) 3 -> Node(3: 300)


### Step 4: `get(2)` (Access key 2)
- Key `2` is present in the cache. Move it to the head of the list, as it's now the most recently used.
- The order of the list changes.

Doubly Linked List (Cache Order): [2: 200] <-> [3: 300] <-> [1: 100]

Hash Table: 1 -> Node(1: 100) 2 -> Node(2: 200) 3 -> Node(3: 300)


### Step 5: `put(4, 400)` (Insert key 4 with value 400)
- The cache is full (capacity = 3). The least recently used item (`1: 100` at the tail) is removed.
- Key `4` is inserted at the head.

Doubly Linked List (Cache Order): [4: 400] <-> [2: 200] <-> [3: 300]

Hash Table: 2 -> Node(2: 200) 3 -> Node(3: 300) 4 -> Node(4: 400)


In this step:
- Key `1` was removed because it was the least recently used.
- Key `4` was inserted and moved to the head, making it the most recently used.

## Data Structures in Action:

1. **Doubly Linked List**: Efficiently handles the **removal** of the least recently used item (tail) and **moving** accessed/inserted items to the front (head).
2. **Hash Table**: Provides constant-time access to cache items for lookups and updates.

## Key Points:
- **Cache Access**: When a key is accessed (via `get`), it is moved to the head, making it the most recently used.
- **Cache Eviction**: When the cache is full, the least recently used item (tail of the list) is removed.
- **Hash Table**: Provides O(1) access to nodes, ensuring the cache operates efficiently.

## Performance:
- **Time Complexity**: O(1) for both `get` and `put` operations due to the combined use of a hash table and doubly linked list.
- **Space Complexity**: O(n), where `n` is the cache capacity (to store the hash table and doubly linked list nodes).
