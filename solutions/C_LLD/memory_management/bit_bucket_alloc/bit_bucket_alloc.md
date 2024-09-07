## Explanation:

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
