#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

int verbose = 0;

int main(int argc, char **argv)
{
    char *stun_server = "";

    static char usage[] = "usage: [-h] [-H STUN_HOST] [-t ttl] [-P STUN_PORT] [-s punch server] [-d id] [-i SOURCE_IP] [-p SOURCE_PORT] [-v verbose]\n";
    int opt;
    while ((opt = getopt(argc, argv, "H:h:t:P:p:s:d:i:v")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printf("%s", usage);
            break;
        case 'H':
            stun_server = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case '?':
        default:
            printf("invalid option: %c\n", opt);
            printf("%s", usage);

            return -1;
        }
    }

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s <= 0)
    {
        return -1;
    }

    struct sockaddr_in servAddr = {0};
    servAddr.sin_port = htons(5555);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(stun_server);
    //servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.20");
    char buf[0x40] = {0};

    if (-1 == sendto(s, buf, 0x10, 0, (struct sockaddr *)&servAddr, sizeof(servAddr)))
    {
        // sendto() barely failed
        return -1;
    }
}