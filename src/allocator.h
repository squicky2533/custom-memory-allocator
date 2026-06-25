#ifndef ALLOCATOR_H 
#define ALLOCATOR_H 

#include <stddef.h> 

typedef struct block{
    size_t size ;
    int free ; 
    struct block *next; 
}block_t;


block_t *find_free_block(size_t size);
block_t *request_space(size_t size);
void *my_malloc(size_t size);
void my_free(void *ptr);
void print_heap(void);

#endif
