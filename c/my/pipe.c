#include <sys/socket.h>
#include <unistd.h>
#include <sys/stat.h>
#include <strings.h>
#include "string.h"
#include <stdio.h>
#include "stdlib.h"
int main()
{
    int mypipe[2],i;
    FILE *log;
    pid_t p;
    if( pipe(mypipe) == -1 )
    {
        perror("创建管道失败");
        return -1;
    }
    log = fopen("pipe.log","w+");

    for(i=0;i<3;i++)
    {
        p = fork();
        if( p<= (pid_t) 0)
        {
            sleep(i);
            close(mypipe[0]);
            char *msg = "process\0";
            fwrite(msg,8,1,log);
            write(mypipe[1],msg,8);
            exit(0);
        }
    }

    char *buf;
    int a = 0;
    while((a = read(mypipe[0],&buf,1)) > 0)
    {
        // printf("收到的消息%c\n",*buf);
        if( buf == '\0')
        {
            printf("你好\n");
        }
        else {
            write(STDOUT_FILENO,&buf,1);
            // printf(" a的值为%d\n",a);
        }
    }

    printf("a的值为%d\n",a);
}
