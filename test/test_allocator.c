#include <stdio.h>
#include "../src/allocator.h"

int main(void)
{
    char *ptr = my_malloc(100);

    if (ptr)
    {
        ptr[0] = 'A';
        ptr[1] = 'B';
        ptr[2] = 'C';
        ptr[3] = '\0';

        printf("%s\n", ptr);
    }

    return 0;
}