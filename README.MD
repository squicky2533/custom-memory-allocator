<h1 id="custom-memory-allocator" align="center">custom-memory-allocator</h1>

## Table of Contents
- [Table of Contents](#table-of-contents)
    - [**Contents**](#contents)
    - [**What this implements**](#what-this-implements)
    - [**Further improvements**](#further-improvements)
    - [**Build \& Run**](#build--run)

A small educational example of a simple custom memory allocator in C.

This repository demonstrates a minimal allocator that provides primitives
to locate a free memory block and request new memory from the OS using
`sbrk`. It's intended for learning and experimentation rather than
production use.

#### **Contents**
- **Source:** [src/allocator.c](src/allocator.c), [src/allocator.h](src/allocator.h)
- **Test / Example:** [test/test_allocator.c](test/test_allocator.c)
- **Build script:** [Makefile](Makefile)

#### **What this implements**
- A `block_t` structure representing a memory block with fields:
  - `size`: the size of the user allocation
  - `free`: boolean-like flag indicating whether the block is free
  - `next`: pointer to the next block in a singly-linked list
- `find_free_block(size_t size)` — scans the list for a free block whose
  `size >= requested size` and returns it or `NULL`.
- `request_space(size_t size)` — requests raw memory from the OS with
  `sbrk` and initializes a new `block_t`.

#### **Further improvements**

- [ ] Implement `malloc` and `free` wrappers that use `find_free_block` and `request_space`.
- [ ] Add splitting of larger free blocks so allocations can reuse space efficiently.
- [ ] Add coalescing of adjacent free blocks when freeing to reduce fragmentation.
- [ ] Design and apply proper alignment and block metadata layout (8/16-byte alignment).
- [ ] Replace or optionally support `mmap` (or `posix_memalign`) instead of relying solely on `sbrk`.
- [ ] Add thread-safety (mutexes, per-thread arenas, or lock-free strategies).
- [ ] Improve error handling and defensive checks (null returns, overflow checks).
- [ ] Add automated unit tests, benchmarks, and a CI workflow to validate behavior and performance.
- [ ] Add documentation: API reference, design notes, and usage examples beyond the simple test.

#### **Build & Run**

Build the test executable (Makefile compiles sources and produces
`bin/allocator.o` as the runnable):

```sh
make
```

Run the example:

```sh
make run
```

You can also build directly with `gcc` (equivalent to the `Makefile`):

```sh
gcc -Wall -Wextra -g src/allocator.c test/test_allocator.c -o bin/allocator.o
./bin/allocator.o
```

**Example behavior**

The sample test [test/test_allocator.c](test/test_allocator.c) simply calls
`request_space(100)` and prints the allocated block size when successful.