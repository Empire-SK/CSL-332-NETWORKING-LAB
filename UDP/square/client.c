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
    struct sockaddr_in client;

    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc < 0)
        printf("error in socket.\n");

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 3006;

    k = connect(sock_desc, (struct sockaddr *)&client, sizeof(client));
    if (k < 0)
        printf("error in connecting to client.\n");

    len = sizeof(client);
    buf[0] = '1';
    while (buf[0] != '0')
    {
        printf("send: ");
        fgets(buf, 100, stdin);
        sq = atoi(buf);
        sq = sq * sq;
        sprintf(buf, "%d", sq);
        k = sendto(sock_desc, buf, 100, 0, (struct sockaddr *)&client, len);
        printf("sending...\n");
        k = recvfrom(sock_desc, buf, 100, 0, (struct sockaddr *)&client, &len);
        if (k < 0)
            printf("error in receiving.\n");
        printf("received: %s\n", buf);
    }
    close(sock_desc);
}
