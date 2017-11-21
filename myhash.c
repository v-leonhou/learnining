#include "stdio.h"
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    uint32_t b;
    int a = 2;
    b = ~a + 1;
    printf("\n%d\n",b);

    printf("%d\n",~2+1);
    return 0;
}
