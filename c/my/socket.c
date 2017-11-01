#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <errno.h>

int Sock(const char *filename)
{
    struct sockaddr_un name;
    int sock; 
    size_t size;

    sock = socket(PF_LOCAL,SOCK_DGRAM,0);
    if( sock < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    name.sun_family = AF_LOCAL;
    strncpy(name.sun_path,filename,sizeof(name.sun_path));
    name.sun_path[sizeof(name.sun_path)-1] = '\0';

    size = (offsetof(struct sockaddr_un,sun_path)) + strlen(name.sun_path);
    /*siet = SUN_LEN(&name);*/

    if( bind(sock,(struct sockaddr *) &name,size) < 0 )
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    return sock;
}


int Socket(const char *host, int clientPort)
{
    int sock;
    unsigned long inaddr;
    struct sockaddr_in ad;
    struct hostent *hp;
    
    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;

    inaddr = inet_addr(host);
    if (inaddr != INADDR_NONE)
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    else
    {
        hp = gethostbyname(host);
        if (hp == NULL)
            return -1;
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    ad.sin_port = htons(clientPort);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
        return -1;
    return sock;
}

int main()
{



}
