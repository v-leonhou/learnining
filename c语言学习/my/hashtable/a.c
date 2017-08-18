#include <stdio.h>

int main()
{
    char p[10][20];
    char *k = "women";

    char **m = &k;
    // p[0][3] = 'w';
    // p[1][18] = 'j';
    // char (*m)[20] = p;
    printf("%c",*m[3]);
    // char *k =(char *)&p;
    // k = (char *)&p;
    // printf("\n%p\n%p\n",p,k);


    return 2;
}
