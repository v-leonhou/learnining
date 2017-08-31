#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
int main(void)
{
    HashTable ht;
    hash_init(&ht, 2);

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
