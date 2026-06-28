# Custom Memory Allocator (C)

A simple implementation of a dynamic memory allocator in C, built from scratch using `sbrk`.  
This project demonstrates how low-level memory management works internally, including allocation, deallocation, splitting, and coalescing of memory blocks.

---

## Features

- `my_malloc(size_t size)`
  - Allocates memory from the heap
  - Reuses free blocks when available
  - Splits large blocks to reduce fragmentation
  - Aligns memory to 8-byte boundaries

- `my_free(void *ptr)`
  - Marks blocks as free
  - Prevents invalid double-free operations (basic handling)
  - Triggers coalescing of adjacent free blocks

- `my_realloc(void *ptr, size_t size)`
  - Resizes allocated memory blocks
  - Reuses existing block if possible
  - Allocates new block and copies data if needed

- `my_calloc(size_t nmemb, size_t size)`
  - Allocates zero-initialized memory
  - Uses `my_malloc` internally
  - Clears memory using `memset`

- Heap management utilities:
  - `print_heap()` → prints current heap state
  - `check_leaks()` → detects unreleased memory blocks

---

## Memory Management Strategy

This allocator uses a **singly linked list of blocks**:

Each block contains metadata:

```c
typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;