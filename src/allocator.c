#include <stdio.h> 
#include "allocator.h"
 
block_t *head = NULL ; 

block_t *find_free_block(size_t size){
    printf("alocator\n");
    block_t *current = head ; 
    while (current != NULL){
        if(current->free && current->size >= size){
            return current ; 

    }
        current= current->next;
    }

    return NULL ;

}