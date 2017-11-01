#include "stdio.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
void test(int a)
{
    printf("\na的值为%d\n",a);
    a >>= 5;
    printf("\n左移两位后a的值为%d\n",a);
}
int main(void)
{
    // char *a = "women",*b = "hello",*c = "world";
    // char *p[] = {a,b,c};
    // int *d=NULL,*e=NULL;
    // d = (int *)malloc(2);
    // e = (int *)malloc(3);
    // *d = 20;
    // *e = 30;
    // printf("\nd指针的值%d,e指针的值%d\n",*d,*e);
    test(0);
    test(1);
    test(8);
    test(15);
    test(16);
    test(17);
    test(31);
    test(32);
    test(33);
    test(64);
    test(80);
    
    return 0;
}
