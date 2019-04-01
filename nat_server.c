#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#define DEFAULT_SERVER_PORT 5555

int main(int argc, char** argv)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd==-1)
    {
        printf("create socket failed\n");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DEFAULT_SERVER_PORT);

    int bindret = bind(fd, (const struct sockaddr *)&server_addr,sizeof(server_addr));
    if(bindret==-1)
    {
        printf("bind failed error:%d\n", errno);
        return -1;
    }

    struct sockaddr_in clientaddr[2]={0};
    ssize_t ret = 0;
    char buf[0x10]={0};
    int clients = 0;
    while(1)
    {
        ++clients;
        printf("wait for client...\n");
        struct sockaddr_in remote_addr;
        socklen_t fromlen = sizeof remote_addr;
        ret = recvfrom(fd, buf, 10, 0, (struct sockaddr *)&clientaddr[clients], &fromlen);
        if(ret == -1)
        {
            printf("recvfrom failed error:%d\n", errno);
            break;
        }
        printf("client come: %s:%d\n", inet_ntoa(clientaddr[clients].sin_addr), ntohs(clientaddr[clients].sin_port));
    }
}