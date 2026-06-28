#include <stdio.h>
#include <unistd.h> 
#include <string.h>
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

void *my_malloc(size_t size)
{
    block_t *block;
    block_t *new_block;

    if (size == 0)
        return NULL;

    size = align8(size);

    block = find_free_block(size);

    if (block)
    {
        // SPLIT only for reused blocks
        if (block->size >= size + sizeof(block_t) )
        {
            new_block = (block_t *)((char *)(block + 1) + size);

            new_block->size = block->size - size - sizeof(block_t);
            new_block->free = 1;
            new_block->next = block->next;

            block->size = size;
            block->next = new_block;
        }

        block->free = 0;
        return (void *)(block + 1);
    }

    // NO free block found → request OS
    block = request_space(size);

    if (!block)
        return NULL;

    if (head == NULL)
        head = block;
    else
    {
        // append to list
        block_t *tmp = head;
        while (tmp->next)
            tmp = tmp->next;

        tmp->next = block;
    }

    block->free = 0;
    return (void *)(block + 1);
}

void my_free(void *ptr){
   
    if(!ptr){
        return ; 
    }
    block_t *block = (block_t *)ptr - 1 ; 
    if (block->free)
        return;
    
    block->free = 1;
    coalesce();
}

void coalesce()
{
    block_t *current = head;
    while(current && current->next)
    {
        if(current->free && current->next->free)
        {
            current->size += sizeof(block_t) + current->next->size;
            current->next = current->next->next;
        }
        else
        {
            current = current->next;
        }
    }    
}

void print_heap(void)
{
    block_t *current = head;
    printf("Heap blocks:\n");
    int index = 0;
    while(current != NULL)
    {
        printf(" #%d | addr=%p | size=%zu | %s | netx=%p\n",index, (void *)current, current->size, current->free ? "free" : "allocated", (void *)current->next);
        current = current->next;
        index++;
    }

}

size_t align8(size_t size)
{
    return (size + 7) & ~7;
}

void check_leaks(void)
{
    block_t *current = head;
    int leaks = 0;

    while(current)
    {
        if(current->free == 0)
        {
            leaks++;
        }
        current = current->next;
    }   
    if (leaks)
        printf("Memory leaks detected: %d block(s) not freed.\n", leaks);
    else
        printf("No memory leaks detected.\n");


}

void *my_realloc(void *ptr, size_t size)
{
    if (ptr==NULL)
    {
        return my_malloc(size);
    }

    if(size == 0 )
    {
        my_free(ptr);
        return NULL ; 
    }

    size=align8(size);
    block_t *block = (block_t *)ptr - 1;

    if(block->size >= size)
    {
        return ptr;
    }
    
    void *new_ptr = my_malloc(size);

    if(new_ptr == NULL)
    {
        return NULL;
    }
    memcpy(new_ptr,ptr,block->size);
    my_free(ptr);

    return new_ptr;
}

void my_calloc(size_t nmemb, size_t size)
{
    size_t total_size;
    void *ptr ; 
    
    if(nmemb == 0 || size == 0 )
    {
        return NULL;

    }
    total_size = nmemb * size ; 
    ptr = my_malloc(total_size);

    if(ptr == NULL)
    {
        return NULL;
    }
    
    memset(ptr,0,total_size);

    return  ptr ; 
}
