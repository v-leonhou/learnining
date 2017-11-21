#include "stdio.h"
#include "stdint.h"
int main(void)
{
    int *b,a=2;
    int32_t c;
    *b = ~a + 1;
    c = ~a + 1;
    a = 20;
    printf("%d\n",*b);
    printf("%d\n",c);
    printf("%d\n",~2+1);
    return 0;
}
