#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 32  // Size of each memory block in bytes
#define POOL_SIZE 10   // Total number of blocks in the memory pool

// Memory block structure to represent each block in the pool
typedef struct Block {
    struct Block* next;  // Pointer to the next free block
} Block;

// Memory pool structure
typedef struct MemoryPool {
    Block* freeList;         // Head of the free list
    void* poolStart;         // Pointer to the beginning of the memory pool
} MemoryPool;

// Initialize the memory pool
void initializePool(MemoryPool* pool) {
    pool->poolStart = malloc(POOL_SIZE * BLOCK_SIZE);
    pool->freeList = (Block*)pool->poolStart;

    // Initialize the free list
    Block* current = pool->freeList;
    for (int i = 0; i < POOL_SIZE - 1; i++) {
        current->next = (Block*)((char*)current + BLOCK_SIZE);
        current = current->next;
    }
    current->next = NULL;  // Last block points to NULL
}

// Allocate a block from the memory pool
void* allocateBlock(MemoryPool* pool) {
    if (pool->freeList == NULL) {
        printf("Memory Pool exhausted!\n");
        return NULL;  // No free blocks available
    }

    // Remove a block from the free list and return it
    Block* allocatedBlock = pool->freeList;
    pool->freeList = pool->freeList->next;
    return (void*)allocatedBlock;
}

// Free a block back to the memory pool
void freeBlock(MemoryPool* pool, void* block) {
    // Add the block back to the free list
    Block* freedBlock = (Block*)block;
    freedBlock->next = pool->freeList;
    pool->freeList = freedBlock;
}

// Clean up the memory pool
void destroyPool(MemoryPool* pool) {
    free(pool->poolStart);
    pool->freeList = NULL;
    pool->poolStart = NULL;
}

// Example usage of the memory pool
int main() {
    MemoryPool pool;
    initializePool(&pool);

    // Allocate some blocks
    void* block1 = allocateBlock(&pool);
    void* block2 = allocateBlock(&pool);
    void* block3 = allocateBlock(&pool);

    // Print the addresses of allocated blocks
    printf("Block 1 allocated at address: %p\n", block1);
    printf("Block 2 allocated at address: %p\n", block2);
    printf("Block 3 allocated at address: %p\n", block3);

    // Free a block
    freeBlock(&pool, block2);
    printf("Block 2 freed.\n");

    // Allocate another block (reusing the freed block)
    void* block4 = allocateBlock(&pool);
    printf("Block 4 allocated at address (should reuse Block 2's space): %p\n", block4);

    // Clean up the memory pool
    destroyPool(&pool);

    return 0;
}
