#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

extern int a;
extern void women();

// extern uint32_t _string_hash_val(char *key);

int main(void)
{

    printf("\nomen   %d\n",a);
    a = 2000;
    women();
    printf("\nomen   %d\n",a);
    // int a[5],i;
    // char* b[] = {"women","women22","wojjjmen","wnihaoomen","womwojjjwen"};
    // for(i=0;i<5;i++)
    // {
    //     a[i] = _string_hash_val(b[i]);
    //     printf("%s的哈希值为%d\n",b[i],a[i]);
    // }
    //
    //
    // HashTable ht;
    // hash_init(&ht, 4);
    //
    // int a = 118;
    // int b = 119;
    //
    // hash_add(&ht, "订单2355", &a);
    // hash_add(&ht, "订单2399", &a);
    // hash_add(&ht, "订单2388", &a);
    // hash_add(&ht, "订单2333", &a);
    //
    //
    // Bucket  *find_bucket,*b2;
    // find_bucket = hash_get(&ht, "订单2333");
    //
    // hash_del(&ht, find_bucket);
    // hash_del_by_key(&ht, "订单2388");
    //
    // hash_add(&ht, "订单9999", &a);
    // hash_add(&ht, "订单8888", &a);
    // hash_add(&ht, "订单7777", &a);
    //
    // hash_foreach(&ht);
    //
    return 0;
}
