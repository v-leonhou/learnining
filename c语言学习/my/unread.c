#include <stdio.h>
#include <ctype.h>

int main()
{
    int i = 0;
    char ch;
    puts("Input an integer followed by a char:");

    while(( ch = getchar()) != EOF && isdigit(ch))
    {
        i = 10*i + ch -48;
    }

    if(ch!= EOF)
    {
        ungetc(ch,stdin);
    }

    printf("\n\ni=%d,next char in buffer = %c\n",i,getchar());
    return 0;

}
