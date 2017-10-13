#include "stdio.h"

typedef struct _Bucket Bucket;
struct _Bucket{
    int length;
    char data[1];
};

struct HashTable{
    int elemUsed;
    int size;
    Bucket *arData;
};


int main(int argc, char const* argv[])
{


    return 0;
}
