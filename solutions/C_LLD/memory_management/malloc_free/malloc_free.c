#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>

/* Define the block size since sizeof will be wrong */
#define BLOCK_SIZE 20

typedef struct s_block *t_block;

struct s_block {
    size_t size;
    t_block next;
    t_block prev;
    int free;
    void *ptr; /* A pointer to the allocated block */
    char data[1];
};

/* Global base pointer */
void *base = NULL;

/* Align size to the nearest multiple of 4 */
#define align4(x) (((((x) - 1) >> 2) << 2) + 4)

/* Extend the heap by adding a new block */
t_block extend_heap(t_block last, size_t s) {
    t_block b;
    b = sbrk(0);
    if (sbrk(BLOCK_SIZE + s) == (void*) -1) {
        /* sbrk fails, return NULL */
        return NULL;
    }
    b->size = s;
    b->next = NULL;
    b->prev = last;
    b->ptr = b->data;
    if (last)
        last->next = b;
    b->free = 0;
    return b;
}

/* Split a block into two */
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

/* Find a free block that fits the size */
t_block find_block(t_block *last, size_t size) {
    t_block b = base;
    while (b && !(b->free && b->size >= size)) {
        *last = b;
        b = b->next;
    }
    return b;
}

/* Get the block structure from a pointer */
t_block get_block(void *p) {
    char *tmp = p;
    return (t_block)(tmp - BLOCK_SIZE);
}

/* Validate the pointer */
int valid_addr(void *p) {
    if (base) {
        if (p > base && p < sbrk(0)) {
            return (p == (get_block(p))->ptr);
        }
    }
    return 0;
}

/* Merge adjacent free blocks */
t_block fusion(t_block b) {
    if (b->next && b->next->free) {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if (b->next)
            b->next->prev = b;
    }
    return b;
}

/* Allocate memory */
void *malloc(size_t size) {
    t_block b, last;
    size_t s = align4(size);

    if (base) {
        /* Find a fitting block */
        last = base;
        b = find_block(&last, s);
        if (b) {
            /* Split if necessary */
            if ((b->size - s) >= (BLOCK_SIZE + 4))
                split_block(b, s);
            b->free = 0;
        } else {
            /* No fitting block, extend the heap */
            b = extend_heap(last, s);
            if (!b)
                return NULL;
        }
    } else {
        /* First time allocation */
        b = extend_heap(NULL, s);
        if (!b)
            return NULL;
        base = b;
    }
    return b->data;
}

/* Allocate memory and initialize to zero */
void *calloc(size_t number, size_t size) {
    size_t *new;
    size_t s4, i;
    new = malloc(number * size);
    if (new) {
        s4 = align4(number * size) >> 2;
        for (i = 0; i < s4; i++)
            new[i] = 0;
    }
    return new;
}

/* Free memory */
void free(void *p) {
    t_block b;

    if (valid_addr(p)) {
        b = get_block(p);
        b->free = 1;
        /* Merge with previous if possible */
        if (b->prev && b->prev->free)
            b = fusion(b->prev);
        /* Merge with next if possible */
        if (b->next)
            fusion(b);
        else {
            /* Free the end of the heap */
            if (b->prev)
                b->prev->next = NULL;
            else
                /* No more blocks */
                base = NULL;
            brk(b);
        }
    }
}

/* Copy data from one block to another */
void copy_block(t_block src, t_block dst) {
    int *sdata, *ddata;
    size_t i;
    sdata = src->ptr;
    ddata = dst->ptr;
    for (i = 0; i * 4 < src->size && i * 4 < dst->size; i++)
        ddata[i] = sdata[i];
}

/* Reallocate memory */
void *realloc(void *p, size_t size) {
    size_t s;
    t_block b, new;
    void *newp;

    if (!p)
        return malloc(size);

    if (valid_addr(p)) {
        s = align4(size);
        b = get_block(p);

        if (b->size >= s) {
            if (b->size - s >= (BLOCK_SIZE + 4))
                split_block(b, s);
        } else {
            /* Try to merge with next block if possible */
            if (b->next && b->next->free &&
                (b->size + BLOCK_SIZE + b->next->size) >= s) {
                fusion(b);
                if (b->size - s >= (BLOCK_SIZE + 4))
                    split_block(b, s);
            } else {
                /* Allocate a new block */
                newp = malloc(s);
                if (!newp)
                    return NULL;
                new = get_block(newp);
                /* Copy data from old block to new block */
                copy_block(b, new);
                /* Free the old block */
                free(p);
                return newp;
            }
        }
        return p;
    }
    return NULL;
}

/* FreeBSD's reallocf */
void *reallocf(void *p, size_t size) {
    void *newp = realloc(p, size);
    if (!newp)
        free(p);
    return newp;
}

void print_block_info(const char *msg, void *ptr) {
    if (ptr) {
        printf("%s: %p\n", msg, ptr);
    } else {
        printf("%s: NULL\n", msg);
    }
}

int main() {
    // Test malloc
    printf("Testing malloc:\n");
    void *ptr1 = malloc(100);
    print_block_info("Allocated 100 bytes", ptr1);

    // Test calloc
    printf("\nTesting calloc:\n");
    void *ptr2 = calloc(10, 20);  // Allocates 200 bytes and initializes to 0
    print_block_info("Allocated 200 bytes with calloc", ptr2);

    // Test realloc
    printf("\nTesting realloc:\n");
    ptr1 = realloc(ptr1, 150);  // Resize to 150 bytes
    print_block_info("Reallocated to 150 bytes", ptr1);

    // Test reallocf
    printf("\nTesting reallocf:\n");
    void *ptr3 = reallocf(ptr2, 300);  // Resize to 300 bytes
    print_block_info("Reallocated to 300 bytes with reallocf", ptr3);

    // Free allocated memory
    printf("\nTesting free:\n");
    free(ptr1);
    free(ptr3);

    // Allocate and initialize new blocks
    printf("\nAllocating new blocks:\n");
    void *ptr4 = malloc(50);
    print_block_info("Allocated 50 bytes", ptr4);

    void *ptr5 = malloc(200);
    print_block_info("Allocated 200 bytes", ptr5);

    // Freeing allocated blocks
    printf("\nFreeing allocated blocks:\n");
    free(ptr4);
    free(ptr5);

    return 0;
}

