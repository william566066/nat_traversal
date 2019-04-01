#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

int verbose = 0;

int main(int argc, char** argv)
{
    char* stun_server = "";
    char local_ip[16] = "0.0.0.0";
    //uint16_t stun_port = DEFAULT_STUN_SERVER_PORT;
    uint16_t local_port = 34780;
    char* punch_server = NULL;
    uint32_t peer_id = 0;
    int ttl = 10;

    static char usage[] = "usage: [-h] [-H STUN_HOST] [-t ttl] [-P STUN_PORT] [-s punch server] [-d id] [-i SOURCE_IP] [-p SOURCE_PORT] [-v verbose]\n";
    int opt;
    while ((opt = getopt (argc, argv, "H:h:t:P:p:s:d:i:v")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("%s", usage);
                break;
            case 'H':
                stun_server = optarg;
                break;
            case 't':
                ttl = atoi(optarg);
                break;
            case 'P':
                //stun_port = atoi(optarg);
                break;
            case 'p':
                local_port = atoi(optarg);
                break;
            case 's':
                punch_server = optarg;
                break;
            case 'd':
                peer_id = atoi(optarg);
                break;
            case 'i':
                strncpy(local_ip, optarg, 16);
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

    char ext_ip[16] = {0};
    uint16_t ext_port = 0;

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s <= 0)  {  
        return -1; 
    }

    struct sockaddr_in servAddr = {0};
    servAddr.sin_port = htons(5555);
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(stun_server);
    //servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.20");
    char buf[0x40] = {0};

    if (-1 == sendto(s, buf, 0x10, 0, (struct sockaddr *)&servAddr, sizeof(servAddr))) {
            // sendto() barely failed
            return -1;
        }
    
}