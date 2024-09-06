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

