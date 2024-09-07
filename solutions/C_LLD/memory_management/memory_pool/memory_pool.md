## Memory Pool Allocation

### Explanation:

#### Memory Pool:
A chunk of memory (`POOL_SIZE * BLOCK_SIZE`) is pre-allocated and divided into fixed-size blocks of `BLOCK_SIZE`.

#### Free List:
The memory pool is managed using a free list. Each block has a pointer to the next free block.

#### Allocation:
When a block is requested, a block is removed from the free list and returned.

#### Deallocation:
When a block is freed, it is added back to the free list, making it available for future allocations.

#### Efficiency:
This design minimizes fragmentation and the overhead associated with frequent dynamic allocations, making it ideal for scenarios where
memory blocks of fixed sizes are frequently allocated and freed.

---

### Key Functions:

- **`initializePool`**: Initializes the memory pool and sets up the free list.
- **`allocateBlock`**: Allocates a block from the memory pool.
- **`freeBlock`**: Returns a block to the pool.
- **`destroyPool`**: Cleans up the memory pool when it's no longer needed.

---
