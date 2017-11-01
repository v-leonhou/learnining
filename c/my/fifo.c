#include <sys/socket.h>
#include <unistd.h>
#include <sys/stat.h>
#include <strings.h>
#include <stdio.h>

int main()
{
    FILE *a;
    int b;
    pid_t p = 0;
    if( access("/tmp/sock.sock",F_OK) == 0 )
    {
        if( unlink("/tmp/sock.sock") == -1 )
        {
            perror("deleted file fail\n");
        }
    }
    b = mkfifo("/tmp/sock.sock", 0777);
    p = fork();
    if( p < (pid_t) 0)
    {
        printf("fork faild \n");
        perror("fork faild perror \n ");
    }
    if( p == (pid_t) 0 )
    {
        printf("你好，我是子进程 \n");
        sleep(2);
        a = fopen("/tmp/sock.sock","w");
        if( fprintf(a,"子进程写入数据，hello world !") == -1 )
        {
            perror("子进程写入数据失败!\n");
        }
    }
    if( p > 0)
    {
        char buf[200];
        printf("我是父进程\n");

        a = fopen("/tmp/sock.sock","r");
        fscanf(a,"%s",buf);
        printf("我是父进程，读入子进程写入数据\n 接收子进程数据:%s \n",buf);
    }

}
