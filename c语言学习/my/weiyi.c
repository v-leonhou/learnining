#include <stdio.h>
#include <stdlib.h>


//打印一个数字的二进制,10进制整数转换为二进制数，并打印出二进制
void bitcode(int b)
{
    char *a;
    // a = malloc(sizeof(char)*30);
    int k;
    while(b/2)
    {
        k = b%2;
        // printf("二进制数为：%d\n",a);
        sprintf(a,"%d",k);
        b /= 2;
        if( b/2 == 0 )
        {
            sprintf(a,"%d",b);
        }
        // printf("b为：%d\n",b);
    }
    printf("二进制数为：%s\n",a);
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
    // bitcode(a);
    for(int i=0;i<9;i++)
    {
        resize(a[i]);
    }
    return 0;
}
