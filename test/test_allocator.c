#include <stdio.h>
#include "../src/allocator.h"
int main(void)
{
    printf("Test 2: reuse block\n");

    char *a = my_malloc(100);
    my_free(a);

    char *b = my_malloc(50);

    printf("a = %p\n", a);
    printf("b = %p\n", b);

    return 0;
}