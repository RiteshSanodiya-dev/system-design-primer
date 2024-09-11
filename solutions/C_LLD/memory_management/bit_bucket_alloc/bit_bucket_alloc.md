## ★ Explanation:

#### Memory Pool:
The memory pool is a pre-allocated array (`memory_pool`) divided into fixed-size blocks of `BLOCK_SIZE`. In this case, the pool size is 1024
bytes, with each block being 32 bytes.

#### Bit Array:
The `bit_array` tracks which blocks are allocated and which are free. Each bit corresponds to a block of memory, where `0` means the block is
free, and `1` means the block is allocated.

#### Allocation:
The `allocateBlock` function searches for a free block by checking the bits in the `bit_array`. If a free block is found, its corresponding bit
is set to `1` (allocated), and the memory address of the block is returned.

#### Deallocation:
The `freeBlock` function marks a block as free by setting its corresponding bit in the `bit_array` to `0`, making it available for future allocations.

#### Efficiency:
The bit array allows for efficient memory management with constant-time allocation and deallocation, making it ideal for managing fixed-size memory blocks. 

You can extend this code with additional error handling, dynamic resizing, or support for larger memory pools to handle more complex scenarios.



## ★ Pictorial representation

**Memory Pool Visualization:**
Imagine the memory pool visually as follows, with each # representing 10 bytes (1 block):

```python
   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 |
   |---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|----|----|----|
   | B1| B1| B1| B1| B1| B1| B1| B1| B1| B1| B2 | B2 | B2 | B2 | B2 | B2 | B2 | B2 | B2 | B2 |
                                           ^
   |_________________block 1_______________|___________________block 2_______________________|

```

**Execution of free_blocks(block1):**
- The pointer `block1` points to the first block of the memory pool (`memory_pool[0]`).
- In `free_blocks`, pointer arithmetic calculates:

  ```c
   int block_index = ((char*)block1 - memory_pool) / BLOCK_SIZE;
  ```
- `((char*)block1 - memory_pool) ` evaluates to 0 - 0, which is 0.
- Therefore, `block_index = 0 / 10 = 0`.
    -It prints: `Block index: 0`.
  
**Execution of free_blocks(block2):**
- The pointer `block2` points to the second block of the memory pool (`memory_pool[10]`).
- Similarly, the calculation becomes: ```c int block_index = ((char*)block2 - memory_pool) / BLOCK_SIZE; ```
    - `((char*)block2 - memory_pool)` evaluates to 10 - 0, which is 10.
    - Therefore, `block_index = 10 / 10 = 1`.
- It prints: `Block index: 1`.





