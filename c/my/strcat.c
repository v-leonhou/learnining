#include <string.h>
#include <stdarg.h>

char * concat(const char *str,...)
{
    va_list ap,ap2;
    size_t total = 1;
    const char *s;
    char *result;

    va_start(ap, str);
    va_copy(ap2, ap);

    for(s=str; s != NULL;s = va_arg(ap,const char *))
        total += strlen(s);

    va_end(ap);

    result = (char *) malloc(total);

    if( result != NULL)
    {
        result[0] = '\0';

        for(s=str; s != NULL; s = va_arg(ap2,const char *))
            strcat(result,s);
    }

    va_end(ap2);

    return result;
}


int main()
{




}
