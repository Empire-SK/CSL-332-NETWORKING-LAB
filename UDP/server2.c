#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void main()
{
    char buf[100];
    int k, sq;
    socklen_t len;
    int sock_desc;
    struct sockaddr_in server;

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc < 0)
        printf("error in socket creation.\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3006;

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k < 0)
        printf("error in binding.\n");

    len = sizeof(server);
    while (buf[0] != '0')
    {
        k = recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&server, &len);
        if (k < 0)
            printf("error in receiving.\n");
        printf("received: %s", buf);
        printf("\nsend: ");
        fgets(buf, 100, stdin);
        sq = atoi(buf);
        sq = sq * sq;
        sprintf(buf, "%d", sq);
        k = sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&server, len);
        printf("sending...\n");
    }
    close(sock_desc);
}
