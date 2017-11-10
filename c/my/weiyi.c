#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

//打印一个数字的二进制,10进制整数转换为二进制数，并打印出二进制
void bitcode(int b)
{
    printf("十进制数%d转化为二进制数为:",b);
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
    int a[10] = {2,4,6,8,9,14,15,29,68,34};
    for(int i=0;i<9;i++)
    {
        bitcode(a[i]);
    }
    return 0;
}
