# malloc() and free() implimentation

**reference :** https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf


# 1. Introduction

## What is malloc?

If you don’t even know the name, you might begin to learn C in the Unix environment prior to reading this tutorial. For a
programmer, `malloc` is the function to allocate memory blocks in a C program. Most people don’t know what is really behind
it, and some even think it's a syscall or a language keyword. In fact, `malloc` is nothing more than a simple function and
can be understood with a little C knowledge and almost no system knowledge.

The purpose of this tutorial is to code a simple `malloc` function in order to understand the underlying concepts. We will
not code an efficient `malloc`, just a basic one. However, the concept behind it can be useful to understand how memory is
managed in everyday processes and how to deal with block allocation, reallocation, and freeing.

From a pedagogical standpoint, this is a good C practice. It is also a good document to understand where your pointers come
from and how things are organized in the heap.

## What is malloc?

`malloc(3)` is a Standard C Library function that allocates (i.e., reserves) memory chunks. It complies with the following rules:

- `malloc` allocates at least the number of bytes requested.
- The pointer returned by `malloc` points to an allocated space (i.e., a space where the program can read or write successfully).
- No other call to `malloc` will allocate this space or any portion of it, unless the pointer has been freed before.
- `malloc` should be tractable: it must terminate as soon as possible (it should not be NP-hard!).
- `malloc` should also provide resizing and freeing.

The function obeys the following signature:

```c
void* malloc(size_t size);
```

Where size is the requested `size`. The returned pointer should be `NULL` in case of failure (no space left).

# 2. The Heap and the `brk` and `sbrk` Syscalls

Prior to writing a first `malloc`, we need to understand how memory is managed in most multitask systems. We will maintain an abstract
point of view for this section, as many details are system and hardware dependent.

## 2.1 The Process’s Memory

Each process has its own virtual address space dynamically translated into physical memory address space by the MMU (Memory Management Unit)
and the kernel. This space is divided into several parts. All we need to know is that we find at least some space for the code, a stack where
local and volatile data are stored, some space for constant and global variables, and an unorganized space for the program’s data called the heap.

The heap is a continuous (in terms of virtual addresses) space of memory with three bounds:

- A starting point
- A maximum limit (managed through sys/resource.h’s functions `getrlimit(2)` and `setrlimit(2)`)
- An end point called the **break**

The break marks the end of the mapped memory space, which is the part of the virtual address space that corresponds to real memory. Figure 1 sketches the memory organization.

![image](https://github.com/user-attachments/assets/dbf28fa0-2b4d-4309-ba66-40a53599d3d3)

In order to code a `malloc`, we need to know where the heap begin and the break position, and of course we need to be able to move the break.
This the purpose of the two syscalls `brk` and `sbrk`.

## 2.2 `brk(2)` and `sbrk(2)`

We can find the description of these syscalls in their manual pages:

```c
int brk(const void *addr);
void* sbrk(intptr_t incr);
```
- `brk(2)` places the break at the given address `addr` and returns `0` if successful, `-1` otherwise. The global errno symbol indicates the
   nature of the error.
- `sbrk(2)` moves the break by the given increment (in bytes). Depending on system implementation, it returns the previous or the new break address.
   On failure, it returns `(void *)-1` and sets `errno`. On some systems, `sbrk` accepts negative values (in order to free some mapped memory).

Since `sbrk`'s specification does not fix the meaning of its result, we won’t use the returned value when moving the break. However, we can use a special case of `sbrk`: when the increment is zero (i.e., `sbrk(0)`), the returned value is the actual break address (the previous and new break addresses are the same). `sbrk` is thus used to retrieve the beginning of the heap, which is the initial position of the break.

We will use sbrk as our main tool to implement malloc. All we need to do is acquire more space (if needed) to fulfill the query.


## 2.3 Unmapped Region and No-Man’s Land

We saw earlier that the break marks the end of the mapped virtual address space: accessing addresses above the break should trigger a bus error.
The remaining space between the break and the maximum limit of the heap is not associated with physical memory by the virtual memory manager of
the system (the MMU and the dedicated part of the kernel).

However, if you know a little about virtual memory (or even think about it for 5 seconds), you'll realize that memory is mapped by pages. Both
physical and virtual memory are organized into pages (or frames, in the case of physical memory) of fixed size. Most of the time, the page size
is significantly larger than a single byte (on most current systems, a page size is 4096 bytes). 

Thus, the break may not always align with the page boundaries.

![image](https://github.com/user-attachments/assets/862d4702-2bc5-41c9-88c6-8295f1e946db)

Figure 2 presents the previous memory organisation with page boundaries. We can see the break may not correspond to a page boundary. What is the status
of the memory betwee the break and the next page boundary ? In fact, this space is available ! You can access (for reading or writing) bytes in this space.
The issue is that you don’t have any clue on the position of the next boundary, you can find it but it is system dependant and badly advise. This no-man’s
land is often a root of bugs: some wrong manipulations of pointer outside of the heap can success most of the time with small tests and fail only when
manipulating larger amount of data.


## 2.4 `mmap(2)`

Even though we won’t use it in this tutorial, you should pay attention to the `mmap(2)` syscall. It has an anonymous mode (usually, `mmap(2)` is used
to directly map files in memory) which can be used to implement `malloc` (either completely or for specific cases).

`mmap` in anonymous mode can allocate a specific amount of memory (by page size granularity), and `munmap` can free it. It is often simpler and more
efficient than the classical `sbrk`-based `malloc`. Many `malloc` implementations use `mmap` for large allocations (more than one page).

OpenBSD’s `malloc` uses only `mmap`, with some quirks to improve security, such as preferring page borders for allocation and leaving holes between pages.


# 3. Dummy `malloc`

First, we will play with `sbrk(2)` to code a dummy `malloc`. This `malloc` is probably the worst one, even though it is the simplest and quite the fastest one.

## 3.1 Principle

The idea is very simple: each time `malloc` is called, we move the break by the amount of space required and return the previous address of the break.
It is simple and fast, taking only three lines of code. However, we cannot perform a real `free`, and `realloc` is impossible.

This `malloc` wastes a lot of space in obsolete memory chunks. It is only here for educational purposes and to try out the `sbrk(2)` syscall. For
learning purposes, we will also add some error management to our `malloc`.


## 3.2 Implementation

```c
/* An horrible dummy malloc */

#include <sys/types.h>
#include <unistd.h>

void *malloc(size_t size)
{
   void *p;
   p = sbrk (0);
   /* If sbrk fails , we return NULL */
   if (sbrk(size) == (void*) -1)
   return NULL;
   return p;
}
```

# 4. Organizing the Heap

In [Section 3](#3-dummy-malloc), we presented a first attempt to code a `malloc` function, but we failed to fulfill all the requirements. In this
section, we will try to find an organization of the heap so that we can have an efficient `malloc` as well as `free` and `realloc` functionalities.


## 4.1 What Do We Need?

If we consider the problem outside of the programming context, we can infer what kind of information we need to solve our issues. Let’s use an
analogy: you own a field and partition it to rent portions of it. Clients ask for different lengths (you divide your field using only one dimension)
which they expect to be continuous. When they are finished, they give you back their portion, so you can rent it again.

On one side of the field, you have a road with a programmable car. You enter the distance between the beginning of the field and the destination
(the beginning of your portion). So, we need to know where each portion begins (this is the pointer returned by `malloc`), and when we are at the
beginning of a portion, we need the address of the next one.

A solution is to put a sign at the beginning of each portion where we indicate the address of the next one (and the size of the current one to avoid
unnecessary computation). We also add a mark to free portions (we put that mark when the client gives it back). Now, when a client wants a portion of
a certain size, we take the car and travel from sign to sign. When we find a portion marked as free and wide enough, we give it to the client and remove
the mark from the sign. If we reach the last portion (its sign has no next portion address), we simply go to the end of the portion and add a new sign.

Now, we can transpose this idea to memory: we need extra information at the beginning of each chunk, indicating at least the size of the chunk, the address
of the next one, and whether it's free or not.

## 4.2 How to Represent Block Information

What we need is a small block at the beginning of each chunk containing the extra information, called **meta-data**. This block contains at least:

- A pointer to the next chunk
- A flag to mark free chunks
- The size of the data of the chunk

Of course, this block of information is stored before the pointer returned by `malloc`.

![image](https://github.com/user-attachments/assets/6e21c562-858c-4552-acc2-1a26fc9a3181)

Figure 3 presents an example of heap organization with meta-data in front of the allocated block. Each chunk of data is composed of a block of
meta-data followed by the block of data. The pointer returned by `malloc` is indicated in the lower part of the diagram; note that it points to
the data block, not the complete chunk.

Now, how do we translate this into C code? This looks like a classic linked list (and it is a linked list), so we write a type for the linked list
with the necessary information inside the members of the list. The type definition is self-describing and presents no surprises:

```c
typedef struct s_block *t_block;

struct s_block {
size_t size;
t_block next;
int free;
};
```

Note the use of a `typedef` to simplify the use of the type. Since we will never use the type without a pointer, we include it in the `typedef`.
This is, in fact, a good practice for linked lists since the list is the pointer, not the block (an empty list is a `NULL` pointer).

It may seem like a waste of space to use an `int` as a flag, but since structs are aligned by default, it won’t change anything. We will see later
how we can shrink the size of the meta-data. Another point we'll cover later is that `malloc` must return aligned addresses.

A frequent question at this point is: how can we create a struct without a working `malloc`? The answer is simple: you just need to know what a struct
really is. In memory, a struct is simply the concatenation of its fields. So, in our example, a struct `s_block` is just 12 bytes
(with 32-bit integers): the first four bytes correspond to the size, the next four to the pointer to the next block, and finally the last four are the
integer `free`.

When the compiler encounters an access to a struct field (like `s.free` or `p->free`), it translates it to the base address of the struct plus the sum
of the lengths of the previous fields. So `p->free` is equivalent to `*((char*)p + 8)`, and `s.free` is equivalent to `*((char*)&s + 8)`. All you have
to do is allocate enough space with `sbrk` for the chunk (i.e., the size of the meta-data plus the size of the data block) and store the address of the
old break in a variable of type `t_block`:

```c
/* Example of using t_block without malloc */
t_block b;
/* save the old break in b */
b = sbrk (0);
/* add the needed space */
/* size is the parameter of malloc */
sbrk(sizeof(struct s_block) + size );
b->size = size;
/* ... */
```

# 5 A First Fit Malloc
In this section, we will implement the classic first-fit `malloc`. The first-fit algorithm is quite simple: we traverse the chunks list 
and stop when we find a free block with enough space for the requested allocation.

## 5.1 Aligned Pointers
It is often required that pointers be aligned to the integer size (which is also the pointer size). In our case, we will consider 
only the 32-bit case. So, our pointer must be a multiple of 4 (32 bits = 4 bytes, of course). Since our meta-data block is already 
aligned, the only thing we need is to align the size of the data block.

### How Do We Do This?
There are several ways to align, one of the more efficient is to add a preprocessor macro using an arithmetic trick. 

First, the arithmetic trick: given any positive integer, dividing (integer division) it by four and then multiplying it by four 
again results in the nearest smaller multiple of four. To obtain the nearest greater multiple of four, we only need to add four 
to it. 

This is quite simple, but it doesn’t work with an integer multiple of four, since it results in the next multiple of four. Let’s 
break it down: let x be an integer such that `x = 4 × p + q` with `0 ≤ q ≤ 3`. 

- If `x` is a multiple of four, `q = 0`, and `x−1 = 4 × (p−1) + 3`, so `((x−1)/4) × 4 + 4 = 4 × p = x`.
- If `x` is not a multiple of four, then `q != 0`, and `x − 1 = 4 × p + (q − 1)` and `0 ≤ q − 1 ≤ 2`, so `(x−1)/4×4 + 4 = 4 × p + 4 = x/4×4 + 4`.

Thus, we have our formula: `(x−1)/4 × 4 + 4` always results in the nearest greater or equal multiple of four.

### How Do We Write This in C?
Dividing and multiplying by four can be expressed using right and left bit-shift operators (`>>` and `<<` in C), which are faster 
than simple multiplication. So our formula can be written in C like this: `(((x-1)>>2)<<2) + 4`

To have a proper macro, we need some extra parentheses:

```c
#define align4(x) (((((x) - 1) >> 2) << 2) + 4)
```

## 5.2 Finding a Chunk: the First Fit Algorithm

Finding a free sufficiently wide chunk is quite simple: We begin at the base address of the heap (saved somehow in our code; we will
see that later), test the current chunk, and if it fits our needs, we return its address. Otherwise, we continue to the next chunk until
we find a fitting one or reach the end of the heap. The only trick is to keep the last visited chunk so the `malloc` function can easily
extend the end of the heap if we find no fitting chunk. 

The code is straightforward. `base` is a global pointer to the starting point of our heap:

```c
t_block find_block(t_block *last, size_t size) {
    t_block b = base;
    while (b && !(b->free && b->size >= size)) {
        *last = b;
        b = b->next;
    }
    return b;
}
```

The function returns a fitting chunk, or `NULL` if none are found. After execution, the argument `last` points to the last visited chunk.


## 5.3 Extending the Heap

Sometimes, we won’t always have a fitting chunk, and especially at the beginning of the program using our `malloc`, we need to extend the
heap. This is quite simple: we move the break and initialize a new block. Of course, we need to update the `next` field of the last block
on the heap.

In later development, we will need to adjust the size of `struct s_block`, so we define a macro holding the size of the meta-data block.
For now, it is defined as:

```c
#define BLOCK_SIZE sizeof(struct s_block)
```

Nothing surprising in this code. We just return `NULL` if `sbrk` fails (and we don’t try to understand why). Note also that since we’re
not sure that `sbrk` returns the previous break, we first save it and then move the break. We could have computed it using `last` and
`last->size`.

```c
t_block extend_heap(t_block last, size_t s) {
    t_block b;
    b = sbrk(0);
    if (sbrk(BLOCK_SIZE + s) == (void*) -1) {
        /* sbrk fails, go to die */
        return NULL;
    }
    b->size = s;
    b->next = NULL;
    if (last) {
        last->next = b;
    }
    b->free = 0;
    return b;
}

```

## 5.4 Splitting Blocks

You may have noticed that we use the first available block regardless of its size (provided that it’s wide enough). If we do that, we will
lose a lot of space (think about it: you ask for 2 bytes and find a block of 256 bytes). 

A first solution is to split blocks: when a chunk is wide enough to hold the requested size plus a new chunk (at least `BLOCK_SIZE + 4`), we
insert a new chunk in the list.

![image](https://github.com/user-attachments/assets/94d20614-c280-4ab2-a702-2151c28db041)

The following function is called only if space is available. The provided size must also be aligned. In this function, we’ll have to do some
pointer arithmetic. To prevent errors, we use a little trick to ensure that all our operations are done with one-byte precision
(remember `p+1` depends on the type pointed to by `p`).

We add another field to `struct s_block` of type character array. Arrays in structures are simply placed directly in the memory block of
the structure at the point where the field is defined. Thus, for us, the array’s pointer indicates the end of the meta-data. C forbids
zero-length arrays, so we define a one-byte-long array, which is why we need to specify a macro for the size of `struct s_block`.

```c
struct s_block {
    size_t size;
    t_block next;
    int free;
    char data[1];
};

/* Of course, update the BLOCK_SIZE macro */
#define BLOCK_SIZE 12 /* 3*4 ... */
```

Note that this extension does not require any modification to `extend_heap` since the new field will not be used directly.

Now, for splitting blocks: this function cuts the block passed as an argument to create a data block of the desired size.
As with the previous function, `s` is already aligned. The following code illustrates how this is done:

```c
void split_block(t_block b, size_t s) {
    t_block new;
    new = (t_block)(b->data + s);
    new->size = b->size - s - BLOCK_SIZE;
    new->next = b->next;
    new->free = 1;
    b->size = s;
    b->next = new;
}
```

Note the use of `b->data` in pointer arithmetic on line 3. Since the field `data` is of type `char[]`,  we are sure that the sum is
done with byte precision.


### 5.5 The malloc Function

Now, we can implement our `malloc` function. It acts mostly as a wrapper around previous functions. We need to align the requested
size, test if this is the first time `malloc` is called, and handle everything else that has been previously described.

First, remember from Section 5.2 that the function `find_block` uses a global variable `base`. This variable is defined as follows:

```c
void *base = NULL;
```

It is a `void` pointer and is initialized to `NULL`. The first thing our `malloc` does is test `base`. If it is `NULL`, then this is
the first time we’re called; otherwise, we start the previously described algorithm.

Our `malloc` function follows these steps:

1. First, align the requested size.
2. If `base` is initialized:
   - Search for a free chunk wide enough.
   - If we find a chunk:
     - Try to split the block (the difference between the requested size and the size of the block should be enough to store the
       meta-data and a minimal block (4 bytes)).
     - Mark the chunk as used (`b->free = 0`).
   - Otherwise, extend the heap.

Note that in `find_block`, the pointer to the last visited chunk is stored in `last`, so we can access it during the extension without
traversing the whole list again.

3. If `base` is not initialized:
   - Extend the heap (which is empty at that point).

Note that our function `extend_heap` works here with `last = NULL`. Also, each time we fail, we silently return `NULL` as specified by
the `malloc` specification.

The following code presents the `malloc` function:

```c
void *malloc(size_t size) {
    t_block b, last;
    size_t s;
    s = align4(size);
    if (base) {
        /* First, find a block */
        last = base;
        b = find_block(&last, s);
        if (b) {
            /* Can we split? */
            if ((b->size - s) >= (BLOCK_SIZE + 4))
                split_block(b, s);
            b->free = 0;
        } else {
            /* No fitting block, extend the heap */
            b = extend_heap(last, s);
            if (!b)
                return (NULL);
        }
    } else {
        /* First time */
        b = extend_heap(NULL, s);
        if (!b)
            return (NULL);
        base = b;
    }
    return (b->data);
}
```


## 6 calloc, free and realloc

### 6.1 calloc

`calloc(3)` is quite straightforward:

- First, do the `malloc` with the right size (product of the two operands).
- Set all bytes in the block to 0.

We use a little trick: the data block size in the chunk is always a multiple of 4, so iterate in 4-byte steps. For this, we use our new
pointer as an unsigned integer array. 

The code is straightforward (see Listing 2).

#### Listing 2: The `calloc` function

```c
void *calloc(size_t number, size_t size) {
    size_t *new;
    size_t s4, i;
    new = malloc(number * size);
    if (new) {
        s4 = align4(number * size) >> 2;
        for (i = 0; i < s4; i++)
            new[i] = 0;
    }
    return (new);
}
```

### 6.2 free

A quick implementation of `free(3)` can be quite simple, but this does not mean that it is convenient. We have two
issues: finding the chunk to be freed and avoiding space fragmentation.

#### 6.2.1 Fragmentation: The malloc illness

A major issue with `malloc` is fragmentation: after several uses of `malloc` and `free`, we end up with a heap divided
into many chunks that are individually too small to satisfy a large `malloc`, while the entire free space would have been
sufficient. This issue is known as the space fragmentation problem.

While we cannot avoid extra fragmentation due to our algorithm without changing it, some other sources of fragmentation can
be avoided. 

When we select a free chunk wide enough to hold the requested allocation and another chunk, we split the current chunk. While
this offers better usage of memory (the new chunk is free for further reservation), it introduces more fragmentation.

A solution to reduce some fragmentation is to merge free chunks. When we free a chunk and its neighbors are also free, we can
merge them into one larger chunk. All we need to do is to test the next and previous chunks. But how do we find the previous
block? We have several solutions:

- Search from the beginning, which is particularly slow (especially if we already do a search for the freed chunk).
- If we already do a search for the current chunk, we could keep a pointer to the last visited chunk (as for `find_block`).
- Double link our list.

We choose the last solution; it’s simpler and allows us to find the target chunk efficiently. So, we modify (again) our
`struct s_block`, but since we have another pending modification (see the next section), we will present the modification later.

So, all we have to do now is merging. We first write a simple merge function that merges a chunk with its successor. Merging with
the predecessor will just involve a test and a call with the appropriate chunk. In the code, we use our new field `prev` for the
predecessor.


```c
t_block fusion(t_block b) {
    if (b->next && b->next->free) {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if (b->next)
            b->next->prev = b;
    }
    return b;
}
```

### 6.2.2 Finding the Right Chunk

The other issue with `free` is finding the correct chunk efficiently with only the pointer returned by `malloc`. There are
several concerns:

- **Validating the Input Pointer:** Is it really a `malloc`-ed pointer?
- **Finding the Meta-Data Pointer**

We can eliminate most invalid pointers with a quick range test: if the pointer is outside the heap, it cannot be valid. The
remaining cases are related to the second concern. How can we be sure that a pointer was obtained by `malloc`?

A solution is to use a magic number inside the block structure. Even better than a magic number is to use the pointer itself.
For example, if we have a field `ptr` pointing to the field `data`, and `b->ptr == b->data`, then `b` is probably (very probably)
a valid block.

Here is the extended structure and functions that verify and access the block corresponding to a given pointer:

```c
/* block struct */
struct s_block {
    size_t size;
    struct s_block *next;
    struct s_block *prev;
    int free;
    void *ptr;  /* A pointer to the allocated block */
    char data[1];
};
typedef struct s_block *t_block;

/* Get the block from an addr */
t_block get_block(void *p) {
    char *tmp;
    tmp = p;
    return (p = tmp -= BLOCK_SIZE);
}

/* Valid addr for free */
int valid_addr(void *p) {
    if (base) {
        if (p > base && p < sbrk(0)) {
            return (p == (get_block(p))->ptr);
        }
    }
    return (0);
}
```
#### 6.2.3 The free function

The `free` function is now straightforward: we verify the pointer and get the corresponding chunk. We then mark it as free and attempt to merge it if possible. We also try to release memory if we’re at the end of the heap.

Releasing memory is simple: if we are at the end of the heap, we just need to set the break to the chunk position with a call to `brk(2)`.

Listing 3 presents our implementation. It follows this structure:

- If the pointer is valid:
  - Get the block address.
  - Mark it as free.
  - If the previous block exists and is free, step backward in the block list and merge the two blocks.
  - Also try to merge with the next block.
  - If we’re at the last block, release memory.
  - If there are no more blocks, revert to the original state (set base to `NULL`).
- If the pointer is not valid, silently do nothing.

### 6.3 Resizing chunks with realloc

The `realloc(3)` function is almost as straightforward as `calloc(3)`. Basically, we need a memory copy operation. We won’t use the provided `memcpy`, since we can handle it more efficiently (sizes are available in blocks and are aligned).

The copy operation is straightforward:

### Free Function Implementation

```c
/* The free */
void free(void *p)
{
    t_block b;
    if (valid_addr(p))
    {
        b = get_block(p);
        b->free = 1;
        /* Fusion with previous if possible */
        if (b->prev && b->prev->free)
            b = fusion(b->prev);
        /* Then fusion with next */
        if (b->next)
            fusion(b);
        else
        {
            /* Free the end of the heap */
            if (b->prev)
                b->prev->next = NULL;
            else
                /* No more blocks! */
                base = NULL;
            brk(b);
        }
    }
}
```

```c
/* Copy data from block to block */
void copy_block(t_block src, t_block dst)
{
    int *sdata, *ddata;
    size_t i;
    sdata = src->ptr;
    ddata = dst->ptr;
    for (i = 0; i * 4 < src->size && i * 4 < dst->size; i++)
        ddata[i] = sdata[i];
}
```


### Realloc Implementation

A very naive (but working) `realloc` follows this algorithm:
- Allocate a new block of the given size using `malloc`;
- Copy data from the old one to the new one;
- Free the old block;
- Return the new pointer.

Of course, we want something a little bit more efficient: we don’t want a new allocation if we have enough room where we are. The
different cases are thus:
- If the size doesn’t change, or the extra-available size (due to alignment constraints, or if
  the remaining size was too small to split) is sufficient, we do nothing;
- If we shrink the block, we try a split;
- If the next block is free and provides enough space, we merge and try to split if necessary.

The following code (Listing 4) presents our implementation. Note that `realloc(NULL, s)` is valid and should be replaced by `malloc(s)`.


### The `realloc` Function

```c
/* The realloc */
/* See realloc(3) */
void *realloc(void *p, size_t size)
{
    size_t s;
    t_block b, new;
    void *newp;

    if (!p)
        return (malloc(size));

    if (valid_addr(p))
    {
        s = align4(size);
        b = get_block(p);

        if (b->size >= s)
        {
            if (b->size - s >= (BLOCK_SIZE + 4))
                split_block(b, s);
        }
        else
        {
            /* Try fusion with next if possible */
            if (b->next && b->next->free &&
                (b->size + BLOCK_SIZE + b->next->size) >= s)
            {
                fusion(b);
                if (b->size - s >= (BLOCK_SIZE + 4))
                    split_block(b, s);
            }
            else
            {
                /* Good old realloc with a new block */
                newp = malloc(s);
                if (!newp)
                    /* We’re doomed! */
                    return (NULL);

                /* I assume this works! */
                new = get_block(newp);
                /* Copy data */
                copy_block(b, new);
                /* Free the old one */
                free(p);
                return (newp);
            }
        }
        return (p);
    }
    return (NULL);
}
```

#### 6.3.1 FreeBSD’s `reallocf`

FreeBSD provides another `realloc` function: `reallocf(3)`, which frees the given pointer in any case (even if the reallocation fails). This is
just a call to `realloc` and a `free` if we get a NULL pointer. The code is as follows:

```c
/* The reallocf */
/* See reallocf(3) */
void *reallocf(void *p, size_t size)
{
    void *newp;
    newp = realloc(p, size);
    if (!newp)
        free(p);
    return (newp);
}
```

### 6.4 Putting Things Together

All that's needed now is to integrate modifications done to the block structure in the previous code. We only need to:

- Rewrite `split_block` and `extend_heap`
- Redefine `BLOCK_SIZE`


### Block Structure and Functions

```c
/* block struct */
struct s_block {
    size_t size;
    struct s_block *next;
    struct s_block *prev;
    int free;
    void *ptr; /* A pointer to the allocated block */
    char data[1];
};
typedef struct s_block *t_block;

/* Define the block size since sizeof will be wrong */
#define BLOCK_SIZE 20

/* Split block according to size. */
/* The b block must exist. */
void split_block(t_block b, size_t s) {
    t_block new;
    new = (t_block)(b->data + s);
    new->size = b->size - s - BLOCK_SIZE;
    new->next = b->next;
    new->prev = b;
    new->free = 1;
    new->ptr = new->data;
    b->size = s;
    b->next = new;
    if (new->next)
        new->next->prev = new;
}

/* Add a new block at the end of the heap */
/* Return NULL if things go wrong */
t_block extend_heap(t_block last, size_t s) {
    int sb;
    t_block b;
    b = sbrk(0);
    sb = (int)sbrk(BLOCK_SIZE + s);
    if (sb < 0)
        return (NULL);
    b->size = s;
    b->next = NULL;
    b->prev = last;
    b->ptr = b->data;
    if (last)
        last->next = b;
    b->free = 0;
    return (b);
}
```
