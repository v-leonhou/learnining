#include <sys/socket.h>
#include <unistd.h>
#include <sys/stat.h>
#include <strings.h>
#include <stdio.h>

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
            char *msg = "i am %d child process\n";
            size_t len;
            fwrite(msg,sizeof(msg),1,log);
            len = write(mypipe[1],msg,sizeof(msg));
        }
    }
    
    char *buf = NULL;
    if( read(mypipe[0],buf,10) )
    {
        printf("%s",buf);
    }
    else {
        printf("读取数据失败\n");
    }
    return 2;

    int j = 5;
    while(j-- > 0)
    {
        char *buf = NULL;
        do{
            read(mypipe[0],buf++,1);
        }while(*buf != '\0');
        fprintf(stdout,"\n接收到子进程%s的数据\n",buf);
    }
}
