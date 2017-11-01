#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

typedef struct
{
    char *name;
}
Widget;

int print_widget(FILE *stream, const struct printf_info *info, const void *const *args)
{
    const Widget *w;
    char *buf;
    int len;

    w = *((const Widget **)(args[0]));
    len = asprintf(&buf,"<Widget %p:%s>",w,w->name);
    if( len == -1)
        return -1;

    len = fprintf(stream,"%*s",(info->left ? -info->width : info->width),buf);

    free(buf);
    return len;
}

int print_widget_arginfo( const struct printf_info *info,size_t n,int *argtypes)
{
    if( n>0)
        argtypes[0] = PA_POINTER;
    return 1;
}

int main(void)
{
    Widget mywidget;
    mywidget.name = "houlu";

    register_printf_function('W', print_widget,print_widget_arginfo);

    printf("|%W|\n",&mywidget);
    printf("|%35W|\n",&mywidget);
    printf("|%-35W|\n",&mywidget);

    return 0;


}

