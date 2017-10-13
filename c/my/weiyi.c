#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

struct array {
    int len;
    char a[0];
};


//打印一个数字的二进制,10进制整数转换为二进制数，并打印出二进制
void bitcode(int b)
{
    printf("十进制数%d:",b);
    int a[200];
    int k,i=0;
    while(b/2)
    {
        k = b%2;
        a[i++] = k;
        b /= 2;
        if( b/2 == 0 )
        {
            a[i++] = b;
        }
    }
    i--;

    while(i>=0)
    {
        printf("%d",a[i--]);
    }
    printf("\n");
}

void resize(int nSize)
{
    int a = nSize;
    nSize -= 1;
	nSize |= (nSize >> 1);
	nSize |= (nSize >> 2);
	nSize |= (nSize >> 4);
	nSize |= (nSize >> 8);
	nSize |= (nSize >> 16);
    nSize +=1;
    printf("%d重新resize之后的值为%d\n",a,nSize);
}


int main()
{
    // unsigned int a,b;
    // b = (4<<2);
    // printf("%d\n",b);
    // a |= (4<<2);
    // printf("%d\n",a);
    int a[10] = {2,4,6,8,9,14,15,29,68,34};
    int i;
    for(i=0;i<9;i++)
    {
        int nSize = a[i];
        resize(nSize);
        bitcode(nSize);
    }
    return 0;

}
