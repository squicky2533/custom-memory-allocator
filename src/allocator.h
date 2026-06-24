#ifndef ALLOCATOR_H 
#define ALLOCATOR_H 

#include <stddef.h> 

typedef struct block{
    size_t size ;
    int free ; 
    struct block *next; 
}block_t;


block_t *find_free_block(size_t size);

#endif
