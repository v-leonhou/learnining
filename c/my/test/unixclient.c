#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char const* argv[])
{
    int sock;
    sock = socket(AF_UNIX,SOCK_STREAM,0);
   // write()
    return 0;
}
