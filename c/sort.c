#include <stdio.h>
//冒泡排序
void maopao(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j] > a[j+1])
            {
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}

//选择排序
void select(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int k = i;
        for(int j=i+1;j<n;j++)
        {
            if(a[j] > a[k]) k =j;
        }
        if(k!=i) {
            int temp = a[i];
            a[i] = a[k];
            a[k] = temp;
        }
    }
}

//插入排序
void insert(int a[],int n)
{
    for(int i=1;i<n;i++)
    {
        int temp = a[i],j;
        for(j=i;j>0 && temp < a[j-1];j--)
        {
            a[j] = a[j-1];
        }

        a[j] = temp;
        // int j = 0,tmp=a[i],k;
        // while(a[j]<a[i] && j<i) {
        //     j++;
        // }
        // k=j;
        // while(j<i) {
        //     a[j+1] = a[j];
        //     j++;
        // }
        // a[k] = tmp;
    }
}

//快速排序(分治法)
void quickSort(int a[],int left,int right)
{
    if(right > left) {
        int tmp = a[left],i = left,j = right;
        while(left<right) {
            while(left<right) {
                if(a[right] < tmp) {
                    a[left] = a[right];
                    break;
                }
                right--;
            }

            while(left<right) {
                if(a[left] > tmp) {
                    a[right] = a[left];
                    break;
                }
                left++;
            }
        }

        a[left] = tmp;
        quickSort(a,i,left-1);
        quickSort(a,left+1,j);
    }
}

//归并排序

//希尔排序

//堆排序


