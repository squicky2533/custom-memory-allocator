#include <stdio.h>
#include "../include/allocator.h"

void test_malloc(void);
void test_free(void);
void test_reuse(void);



int main(void)
{
    test_malloc();
   


    return 0 ; 

}




void test_malloc(void)
{
    printf("=== test_malloc ===\n");

    char *p = my_malloc(100);

    if (p == NULL)
    {
        printf("FAIL\n");
        return;
    }

    p[0] = 'A';
    p[99] = 'Z';

    printf("PASS\n");

    my_free(p);
}