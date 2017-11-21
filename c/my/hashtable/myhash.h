#include "string.h"
#include "stdint.h"

struct Bucket {
    char *key;
    char *val;
    uint32_t h;
    uint32_t next;
};

struct array {
    uint32_t elemUsed;
    uint32_t size;
    uint32_t maskSize;
    char * arData;
};

typedef struct array HashTable;

uint32_t hash_add(HashTable *ht,char* key,char* val);
struct Bucket* hash_get(HashTable *ht,struct Bucket str);
struct Bucket* hash_get_by_key(HashTable *ht,char *key,char* val);
void hash_resize(HashTable *ht);

