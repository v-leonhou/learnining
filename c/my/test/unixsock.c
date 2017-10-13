#include "stddef.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "netdb.h"


#define PORT 1080

int
unix_sock(const char *filename)
{
    int sock;
    struct sockaddr_un addr;
    size_t size;

    sock = socket(PF_UNIX,SOCK_STREAM,0);
    if(sock == -1)
    {
        perror("socket");
        exit(0);
    }

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,filename,sizeof(addr.sun_path));
    addr.sun_path[sizeof(addr.sun_path) - 1] = '\0';
    size = SUN_LEN(&addr);
        // offsetof(struct sockaddr_un,sun_path) + strlen(addr.sun_path);

    if( bind(sock,(struct sockaddr*)&addr,size) < 0)
    {
        perror("bind");
        exit(0);
    }
    return sock;
}

int
inet_sock()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(PF_INET,SOCK_STREAM,0);
    if( sock == -1)
    {
        perror("socket");
        exit(0);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if( bind(sock,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("bind");
        exit(0);
    }
    if( listen(sock,400) < 0 )
    {
        perror("listen");
        exit(0);
    }
    return sock;
}

int test()
{
    struct hostent *test;
    test = gethostbyname("www.baidu.com");
    printf("地址信息:h_name:%s\n",test->h_name);
    printf("h_addrtype:%d\n",test->h_addrtype);
    printf("h_aliases:%s\n",*test->h_aliases);
    printf("h_length:%d\n",test->h_length);

    printf("====================\n");
    struct servent *serv;
    serv = getservbyname("git","tcp");
    printf("s_name:%s\n",serv->s_name);
    printf("s_aliases:%s\n",*serv->s_aliases);
    printf("s_port:%d\n",serv->s_port);
    printf("s_proto:%s\n",serv->s_proto);
    // printf("h_addr:%s\n",test->h_addr);
    return 2;
}

int main(int argc,char *argv[])
{
    size_t a;
    char buf[100];
    short int type;
    test();

    if( argc < 2 )
    {
        printf("usage:select one\n");
        exit(0);
    }

    if( strcmp(argv[1],"20") == 0 )
    {
        printf("port%d\n",PORT);
        a = inet_sock();
        type = 0;
    }
    else {
        a = unix_sock("/tmp/hello.sock");
        type = 1;
    }


    if(a > 0)
    {
        int j=4;
        while(j-->0)
        {
            // if( accept(a,buf,50) )
            // {
            //     printf("读取数据:%s\n",buf);
            // }
        }
    }
    else {
        printf("服务器启动错误\n");
    }

    type == 1 && unlink("/tmp/hello.sock");

    return 0;
}
