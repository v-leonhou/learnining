#include "stdio.h"
#include "string.h"

int test(char **a)
{
    *a = "women";
    // printf("a的值为:%s\n",a);
    return 1;
}

// int test1(int &x,int &y)
// {
//     int tmp;
//     tmp = x;
//     x = tmp;
//     y = tmp;
//     printf("ok");
//     return 1;
// }
//
//
int test2(int *x,int *y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
    // printf("ok");
    return 1;
}

int main(void)
{
    char str[] ={'m','a','t'};
    char str1[4];
    char str2[4] = {'B','U'};
    char str3[] = "tang";
    char str4[] = "tang\0";
    char *str5 = "tang\0";
    printf("str:%ld\n str1:%ld\n str2:%ld\n str3:%ld\n str4:%ld\n str5:%ld\n",sizeof(str),sizeof(str1),sizeof(str2),sizeof(str3),sizeof(str4),strlen(str3));

    return 1;



    // int a = 20,b=30;
    //
    // // test1(a,b);
    // test2(&a,&b);
    //
    // printf("a=%d\tb=%d\n",a,b);
    char *b = "hello";
    // char *b = ;
    // &b = "hello";
    test(&b);

    printf("b的值为%s\n",b);
    return 0;
}
