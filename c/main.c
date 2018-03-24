#include <stdio.h>
#include "sort.c"
#include "search.c"

int main(void)
{
    int a[10] = {0,20,2,6,1,98,32,56,78,21};
    int n = 10;
    // quickSort(a,0,n-1);
    insert(a,n);

    for(int i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}
