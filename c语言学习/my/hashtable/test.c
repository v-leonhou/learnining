#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
int main(void)
{
    // // printf("\nomen   %d\n",a);
    // // a = 2000;
    // int a = 20;
    // a = a>>1;
    // // a -= 1;
    // printf("a的值为%d\n",a);
    // a |= a;
    // // a |= (a>>1);
    // printf("a的值为%d\n",a);
    // // a |= (a>>2);
    // // printf("a的值为%d\n",a);
    // // a |= (a>>4);
    // // printf("a的值为%d\n\n",a);
    //
    // // // int (*p)() = &women;
    // char *p,m='w';
    // p = &m;
    // printf("p的地址为%p\n",p);
    // printf("p的值为%c\n",*p);
    //
    // int *j,k=20;
    // j= &k;
    // printf("j的地址为%p\n",j);
    // printf("j的值为%d\n",*j);

    // char *a,b[] = "womenjjjj";
    // a = b;
    // printf("a的地址为:%p\n",a);
    // printf("a的值为:%s\n",a+2);
    // a[2] = 'j';
    //
    // printf("a的值为:%s\n",a);
    // char *c,*d = "womenjjjj";
    // c = d;
    // printf("c的地址为:%p\n",c);
    // printf("c的值为:%s\n",c);


    // women();
    // *p = &women;
    // // printf("\nomen   %d\n\n\n",a);
    // // printf("bucket max = %d\n\n\n\n",HT_INVALID_IDX);
    HashTable ht;
    hash_init(&ht, 8);

    int a = 118;
    int b = 119;

    hash_add(&ht, "订单2355", &a);
    hash_add(&ht, "订单2399", &a);
    hash_add(&ht, "订单2388", &a);
    hash_add(&ht, "订单2333", &a);

    printf("哈希表大小为%d\n",ht.nTableSize);
    printf("哈希表已使用元素个数为%d\n",ht.nNumUsed);

    Bucket  *find_bucket,*b2;
    find_bucket = hash_get(&ht, "订单2333");

    hash_del(&ht, find_bucket);
    hash_del_by_key(&ht, "订单2388");

    hash_add(&ht, "订单9999", &a);
    hash_add(&ht, "订单8888", &a);
    hash_add(&ht, "订单7777", &a);

    hash_foreach(&ht);

    return 0;
}
