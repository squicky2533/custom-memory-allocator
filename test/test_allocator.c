#include <stdio.h>
#include "../src/allocator.h"

int main(void)
{
    char *ptr = my_malloc(100);

    my_free(ptr);

    block_t *block = (block_t *)ptr - 1;

    printf("free = %d\n", block->free);

    return 0;
}