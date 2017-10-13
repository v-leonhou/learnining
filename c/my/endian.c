#include "stdio.h"

int isBigEndian()
{
    int a = 0x1234;
    char b = *(char *)&a;
    if( b == 0x12 )
    {
        return 1;
    }
    return 0;
}

//union的存放顺序是所有成员都从低地址开始存放
int uniontest()
{
    union hello{
        int a;
        char b;
    }test;
    test.a = 0x1234;
    if(test.b == 0x12)
    {
        return 1;
    }
    return 0;
}

int isDaduan()
{
    union{
        unsigned long bit;
        unsigned char byte[4];
    }te;
    te.byte[0] = 0;
    te.byte[1] = 1;
    te.byte[2] = 0;
    te.byte[3] = 0;
    return te.bit == 256;
}

int main()
{
    char a[7] = {'s','a',0,1,0,0,'d'};
    char b = 20;
    printf("一般方法:\n");
    if( isDaduan() )
    {
        printf("大端序\n");
    }
    else {
        printf("小端序\n");
    }
    // if( isBigEndian() )
    // {
    //     printf("大端序\n");
    // }
    // else {
    //     printf("小端序\n");
    // }
    //
    // printf("union方法:\n");
    // if( uniontest() )
    // {
    //     printf("大端序\n");
    // }
    // else {
    //     printf("小端序\n");
    // }
    // unsigned char buf[4] = "1234";
    return 0;
}
