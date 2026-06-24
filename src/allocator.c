#include <stdio.h>
#include <unistd.h>
#include "allocator.h"

block_t* head = NULL;

block_t* find_free_block(size_t size) {
    block_t* current = head;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

block_t* request_space(size_t size) {
    block_t* block;

    block = sbrk(sizeof(block_t));

    if (block == (void*)-1) {
        return NULL;
    }
    block->size = size;
    block->free = 0;
    block->next = NULL;

    return block;
}