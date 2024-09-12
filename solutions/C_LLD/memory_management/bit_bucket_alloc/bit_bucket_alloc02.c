#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 256  // Total size of the memory pool (using a small value for now, e.g., 1024 can be used later)
#define BLOCK_SIZE 32                   // Size of each block
#define NUM_BLOCKS (POOL_SIZE / BLOCK_SIZE) // Number of blocks in the pool
#define BIT_ARRAY_SIZE ((NUM_BLOCKS + 7) / 8) // Number of bytes needed for bit array

// Memory Pool
char memory_pool[POOL_SIZE];

// Bit array to track allocated blocks (0 = free, 1 = allocated)
char bit_array[BIT_ARRAY_SIZE] = {0}; // Initialize to zero

// Initialize the memory pool by clearing it
void initialize_pool() {
    memset(memory_pool, 0, POOL_SIZE); // Clear the memory pool
    memset(bit_array, 0, sizeof(bit_array)); // Clear the bit array
}

// Allocate a block of memory from the pool
void* allocate_block() {
    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        size_t byte_index = i / 8;          // Calculate the byte index in the bit array
        size_t bit_index = i % 8;           // Calculate the bit index

        // Check if the block is free
        if ((bit_array[byte_index] & (1 << bit_index)) == 0) {
            // Mark block as allocated
            bit_array[byte_index] |= (1 << bit_index);
            return (void*)(memory_pool + (i * BLOCK_SIZE)); // Return pointer to allocated block
        }
    }
    printf("No free blocks available.\n");
    return NULL;
}

// Free a previously allocated block of memory
void free_block(void* ptr) {
    // Ensure the pointer is valid
    if (ptr < (void*)memory_pool || ptr >= (void*)(memory_pool + POOL_SIZE)) {
        printf("Invalid pointer.\n");
        return;
    }

    // Calculate the block index
    size_t block_index = ((char*)ptr - memory_pool) / BLOCK_SIZE;
    if (block_index < 0 || block_index >= NUM_BLOCKS) {
        printf("Invalid block index.\n");
        return;
    }

    // Mark block as free
    size_t byte_index = block_index / 8; // Calculate byte index
    size_t bit_index = block_index % 8;   // Calculate bit index
    bit_array[byte_index] &= ~(1 << bit_index); // Clear the corresponding bit
}

// Display memory pool usage
void display_pool() {
    printf("Memory Pool Usage:\n");
    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        size_t byte_index = i / 8;          // Calculate byte index
        size_t bit_index = i % 8;           // Calculate bit index
        printf("Block %zu: %s\n", i, (bit_array[byte_index] & (1 << bit_index)) ? "Allocated" : "Free");
    }
}

int main() {
    initialize_pool();

    // Allocate some blocks
    void* block1 = allocate_block();
    void* block2 = allocate_block();
    void* block3 = allocate_block();

    // Display the memory pool status
    display_pool();

    // Free a block
    free_block(block2);

    // Display the memory pool status again
    display_pool();

    return 0;
}
