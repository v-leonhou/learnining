#include <sys/socket.h>
#include <unistd.h>
#include <sys/stat.h>
#include <strings.h>
#include <stdio.h>

int main()
{
    int mypipe[2],i,m;
    FILE *f;
    pid_t p;
    if( pipe(mypipe) == -1 )
    {
        perror("创建管道失败");
        return -1;
    }

    for(i=0;i<6;i++)
    {
        p = fork();
        if( p<= (pid_t) 0)
        {
            sleep(i);
            break;
        }
    }

    if( p < 0 )
    {
        perror("创建进程失败");
        return -1;
    }
    else if ( p == 0) {
        close(mypipe[0]);
        if( (f = fdopen(mypipe[1],"w")) == NULL)
        {
            printf("子进程打开管道失败\n");
            return 2;
        }
        fprintf(f,"%d ",i);
        fclose(f);
        return 2;
    }
    else {
        close(mypipe[1]);
        if( (f = fdopen(mypipe[0],"r")) == NULL)
        {
            printf("父进程打开管道失败\n");
            return 2;
        }
        setvbuf(f,NULL,_IONBF,0);
        while(1)
        {
            if( --i < 0)
            {
                break;
            }
            fscanf(f,"%d",&m);
            fprintf(stdout,"\n接收到子进程%d的数据\n",m);
        }
    }
}
