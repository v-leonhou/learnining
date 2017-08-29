#include <stdio.h>
#include <unistd.h>
#define INADDR_NONE ((unsigned long) -1)

int main()
{
    long a;
    a = sysconf(_SC_PAGESIZE);
    printf("内存页的大小为%li\n",a);
    fwrite("women",5,5,stderr);
}
