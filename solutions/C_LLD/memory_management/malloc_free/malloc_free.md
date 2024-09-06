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


