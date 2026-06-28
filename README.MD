# Custom Memory Allocator (C)

A lightweight implementation of a dynamic memory allocator in C, inspired by `malloc`, `free`, `realloc`, and `calloc`.

This project demonstrates how heap memory management works internally using a custom linked-list based allocator.

---

## Features

- Custom `my_malloc`
- Custom `my_free`
- `my_realloc` implementation
- `my_calloc` implementation
- Free block reuse (First-fit strategy)
- Block splitting to reduce fragmentation
- Block coalescing (merge adjacent free blocks)
- Heap visualization (`print_heap`)
- Memory leak detection (`check_leaks`)
- 8-byte memory alignment

---

## How It Works

The allocator manages memory using a linked list of metadata blocks:

```c
typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;