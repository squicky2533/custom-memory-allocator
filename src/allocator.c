#include <stdio.h>
#include <unistd.h> 
#include "allocator.h"

 
block_t *head = NULL ; 

block_t *find_free_block(size_t size){
    block_t *current = head ; 
    while (current != NULL){
        if(current->free && current->size >= size){
            return current ; 

    }
        current= current->next;
    }

    return NULL ;

}

block_t *request_space(size_t size){
    block_t *block ;
    
    block=sbrk(sizeof(block_t) + size);
    
    if(block==(void *)-1){
        return NULL; 
    }
    block->size= size;
    block->free= 0 ;
    block->next = NULL;
    
    return block ; 




}

void *my_malloc(size_t size){
    block_t *block ;
    if(size == 0 ){
        return NULL ; 
    }
    block = find_free_block(size);
    if(block == NULL){
        block = request_space(size);
        if(block == NULL){
            return NULL ; 
        }
        if(head == NULL){
            head = block ; 
        }
        }
    block->free = 0 ;
    return(void *)(block + 1) ;

}

void my_free(void *ptr){
    block_t *block ; 
    if(ptr == NULL){
        return ; 
    }
    block = (block_t *)ptr - 1 ;
    block->free = 1 ; 
}