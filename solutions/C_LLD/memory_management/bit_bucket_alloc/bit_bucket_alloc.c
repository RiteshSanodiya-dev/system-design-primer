#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 1024    // Total size of the memory pool
#define BLOCK_SIZE 32     // Size of each block
#define NUM_BLOCKS (POOL_SIZE / BLOCK_SIZE) // Number of blocks in the pool

// Memory Pool
char memory_pool[POOL_SIZE];

// Bit array to track allocated blocks (0 = free, 1 = allocated)
unsigned int bit_array[NUM_BLOCKS / (sizeof(unsigned int) * 8)] = {0};

// Initialize the memory pool
void initializePool() {
    memset(memory_pool, 0, POOL_SIZE);
    memset(bit_array, 0, sizeof(bit_array));
}

// Allocate a block of memory
void* allocateBlock() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        int index = i / (sizeof(unsigned int) * 8);
        int bit = i % (sizeof(unsigned int) * 8);

        // Check if the block is free
        if ((bit_array[index] & (1 << bit)) == 0) {
            // Mark block as allocated
            bit_array[index] |= (1 << bit);
            return memory_pool + (i * BLOCK_SIZE);
        }
    }
    printf("No free blocks available.\n");
    return NULL;
}

// Free a block of memory
void freeBlock(void* ptr) {
    int block_index = ((char*)ptr - memory_pool) / BLOCK_SIZE;
    if (block_index < 0 || block_index >= NUM_BLOCKS) {
        printf("Invalid pointer.\n");
        return;
    }

    int index = block_index / (sizeof(unsigned int) * 8);
    int bit = block_index % (sizeof(unsigned int) * 8);

    // Mark block as free
    bit_array[index] &= ~(1 << bit);
}

// Display memory pool usage
void displayPool() {
    printf("Memory Pool Usage:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        int index = i / (sizeof(unsigned int) * 8);
        int bit = i % (sizeof(unsigned int) * 8);
        printf("Block %d: %s\n", i, (bit_array[index] & (1 << bit)) ? "Allocated" : "Free");
    }
}

int main() {
    initializePool();
    
    // Allocate some blocks
    void* block1 = allocateBlock();
    void* block2 = allocateBlock();
    void* block3 = allocateBlock();

    // Display the memory pool status
    displayPool();

    // Free a block
    freeBlock(block2);

    // Display the memory pool status again
    displayPool();

    return 0;
}
