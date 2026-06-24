#include <stdio.h>
#include "../src/allocator.h"

int main(void)
{
    block_t *block= request_space(100);
    if(block){
        printf("block created");
        printf("size: %zu\n", block->size);



    }
    return 0 ;


}