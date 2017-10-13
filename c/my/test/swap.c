#include <stdio.h>
#define SWAP_V2(a,b) ( a+=b, b= a-b, a -=b )
#define SWAP_V3(x,y) (x^=y,y^=x,x^=y)

int main()
{
    int a = 20,b = 100;
    volatile int res = 0;
    for(int i=0;i<100000;++i)
        for(int j=0;j<10000;++j)
            res += a;
    // SWAP_V2(a,b);
    printf("V2: a=%d b=\n",res);
    // SWAP_V3(a,b);
    // printf("a=%d b=%d\n",a,b);
    // SWAP_V2(a,a);
    // printf("V4: a=%d b=%d\n",a,b);
    //

    return 0;
}
