#include <stdio.h>
#include "../src/allocator.h"

int main(void)
{
    printf("Allocator project started!\n");
    find_free_block(100);
    return 0;
}