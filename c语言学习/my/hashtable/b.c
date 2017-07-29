#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int main()
{
    char *p;
    typedef struct _test test;
    struct _test {
        int a;
        char b[10];
        char *p;
    };
    test *m;

    p = (char *)malloc(200);
    p = "women";
    // p = 0;
    // print
    m =(test *)(p + 5);
    m->a = 10;
    m->b[0] = 'w';
    m->p = "nihao,hello world";
    printf("m的内存大小为%li\n",sizeof(m));


    // p = "wwwwwwwwkkkkkkk";


    // uint32_t b=10,a = 10;
    // b = -b;
    // int m = sizeof(uint32_t);

    // b = a * sizeof(uint32_t);
    // printf("b的值为%d\n",b);
    // printf("p的内存地址为%p\n",p);
    // printf("p的内存地址为%c\n",*p);
    // printf("p的内存地址为%p\n",p+1);
    // printf("p的内存地址为%c\n",*p+1);
    // printf("m的值为%s\n",p+1);

    return 2;
}
