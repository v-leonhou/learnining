#include <stdio.h>
#include "stdint.h"
#include "string.h"
#include "myhash.h"
#include "stdlib.h"

uint32_t _check_size(uint32_t nSize) /*{{{*/
{
    nSize -= 1;
    nSize |= (nSize >> 1);
    nSize |= (nSize >> 2);
    nSize |= (nSize >> 4);
    nSize |= (nSize >> 8);
    nSize |= (nSize >> 16);
    return nSize + 1;
}

uint32_t _string_hash_val(char *key) /*{{{*/
{
    uint32_t    hash = 0 ;
    size_t      len = strlen(key);
    char        *str = key;
        
    for (; len >= 8; len -= 8) {

        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
        hash = ((hash << 5) + hash) + *str++;
    }

    switch (len) {
        case 7: hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 6: hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 5: hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 4: hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 3: hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 2: hash = ((hash << 5) + hash) + *str++; /* fallthrough... */
        case 1: hash = ((hash << 5) + hash) + *str++; break;
        case 0: break;
    }
    return hash | 0x80000000;
}

void hash_init(HashTable *ht,uint32_t size)
{
    char *data;
    uint32_t mallocSize;
    size = _check_size(size);
    ht->elemUsed = 0;
    ht->size = size;
    ht->maskSize = ~size + 1;
    mallocSize = size * sizeof(uint32_t) + size * sizeof(struct Bucket);
    data = (char*)malloc(mallocSize);
    ht->arData = data + size * sizeof(uint32_t);
    memset(data,-1,size*sizeof(uint32_t));
}

uint32_t hash_add(HashTable *ht,char *key,char *val)
{
    struct Bucket *m;
    if( ht->elemUsed < ht->size  )
    {
        m = hash_get(ht,key);
        if(m != NULL )
        {
            m->val = val;
            return 1;
        }
    }
    else {
        hash_resize(ht);
    }

    uint32_t h,idx;
    char *index;
    h = _string_hash_val(key);
    b.key = key;
    b.val = val;
    b.h = h;
    b.next = -1;


    n = (struct Bucket *)(ht->arData + ht->elemUsed);
    *n = b;

    idx = h | ht->maskSize;
    index = ht->arData + idx;
    if( *index != -1 )
    {
        (*n).next = *index;
    }
    *index = ht->elemUsed;

    ht->elemUsed++;
    return 1;
}

struct Bucket* hash_get(HashTable *ht,char *key)
{
    uint32_t h,idx,nIndex,*m;
    struct Bucket *b;
    h = _string_hash_val(key);
    nIndex = h | ht->maskSize;
    m = (uint32_t*)ht->arData + (int32_t)idx;

    while( *m != -1 )
    {
        b = (struct Bucket *)((struct Bucket *)ht->arData + *(m));
        if( b->key == key )
        {
            return b;
        }
        m = b->next;
    }

    return NULL;

}

struct Bucket* hash_get_by_key(HashTable *ht,char *key,char* val)
{
    uint32_t h,idx;
    h = _string_hash_val(key);
    idx = h | ht->maskSize;

}

void hash_del()
{

}

void hash_resize(HashTable *ht)
{
    char *data,*arData;
    uint32_t tableSize;
    tableSize = ht->size * sizeof(uint32_t) + ht->size * sizeof(struct Bucket);
    data = malloc(tableSize);
    arData = data + ht->size;
    memcpy(arData,ht->arData,ht->size);
    arData = data + ht->size - ht->size;
    memcpy(arData,ht->arData - ht->size,ht->size);
}

void hash_foreach()
{

}


int main()
{
    HashTable ht;
    hash_init(&ht,5);

    return 2;
}
