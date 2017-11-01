#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

int Socket(const char *filename)
{
    struct sockaddr_un name;
    int sock;
    size_t size;

    sock = socket(AF_UNIX,SOCK_STREAM,0);
    if( sock <0 )
    {
        fprintf(stderr,"创建socket失败\n");
        exit(EXIT_FAILURE);
    }
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path,filename,sizeof(name.sun_path));
    name.sun_path[sizeof(name.sun_path) - 1] = '\0';
    //
    // size = offsetof(struct sockaddr_un,sun_path) + strlen(name.sun_path);

    if( connect(sock,(struct sockaddr *)&name,sizeof(struct sockaddr_un)) < 0)
    {
        perror("连接socket失败");
        exit(EXIT_FAILURE);
    }
    return sock;
}

int main()
{
    char *unixsocket = "/var/run/php-fpm.sock",buf[1000];
    int a = Socket(unixsocket),b;
    printf("文件描述符%d\n",a);
    b = write(a,"women\0",sizeof("women\0"));
    if( b < 0)
    {
        perror("写入数据失败\n");
        exit(EXIT_FAILURE);
    }
    printf("写入数据%d\n",b);
    
    // while(1)
    // {
       b = read(a,buf,1000);
       printf("读取数据%d\n",b);
       if( b == 0)
       {
           printf("socket返回数据%s\n",buf);
           // break;
       }
       printf("socket返回数据%s\n",buf);
       close(a);

    // }
    return 0;
}
