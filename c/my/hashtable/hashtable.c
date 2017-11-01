#include "stdio.h"
#include "string.h"

#define HASH_INDEX(ht, key) (hash_str((key)) % (ht)->size)

typedef struct _Bucket
{
    char *key;
    void *value;
    struct _Bucket *next;

} Bucket;

typedef struct _HashTable
{
    int size;
    int elem_num;
    Bucket** buckets;

} HashTable;

static int hash_str(char *key)
{
    int hash = 0;

    char *cur = key;

    while(*cur != '\0') {
        hash += *cur;
        ++cur;

    }

    return hash;

}

// 使用这个宏来求得key在哈希表中的索引
int main()
{
    int i = 0;
    char *p[] = {"women","jjjjj","jkjwome","nihaoma","jjjcwm","woemen","jjawwea"};
    /*scanf(p);*/
        
   /*for( i=0;i< 10;i++ ) */
   while( i < 7 )
   {
       /*scanf(*p);*/
       /*printf("结果:%d",hash_str(p[i]));*/
       printf("结果:%s",p[i]);
       i++;
       /*printf("结果:%s",hash_str(p[i]));*/
       /*printf("结果:%s","women");*/

   }
   return 0;

}
