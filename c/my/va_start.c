#include <stdio.h>
#include <stdarg.h>

void
foo(char *fmt, ...)
{
    va_list ap;
    int d;
    char c, *s;

    va_start(ap, fmt);
    while (*fmt)
        switch (*fmt++) {
            case 's':	      /* string */
                s = va_arg(ap, char *);
                printf("string %s\n", s);
                break;
            case 'd':	      /* int */
                d = va_arg(ap, int);
                printf("int %d\n", d);
                break;
            case 'c':	      /* char */
                /* need a cast here since va_arg only
                   takes fully promoted types */
                c = (char) va_arg(ap, int);
                printf("char %c\n", c);
                break;
        }
    va_end(ap);
}

void print_arg(int count,...)
{
    int i,value;
    va_list arg_ptr;
    va_start(arg_ptr,count);
    for(i=0;i<count;i++)
    {
        value = va_arg(arg_ptr,int);
        printf("position %d = %d\n",i+1,value);
    }
    va_end(arg_ptr);
}

int test(int *a)
{
    *a = 20;
    return 10;
}

int main(void)
{
    int a;
    test(&a);
    printf("%d\n",a);
    // foo("sjjmed1222cm");
    // printf("\n");
    // print_arg(5,7,2,'P','d',"Pd");
    // int a = (int)"Pd";
    // printf("\n%d\n",a);
    // char *p = "womenssddccwjjc";
    // printf("%s\n\n\n",p);
    // while(*p)
    // {
    //     switch(*p++)
    //     {
    //         case 's':
    //             printf("%s\n",p);
    //         case 'd':
    //             printf("%s\n",p);
    //     }
    // }
    return 0;
}


