#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
// #include <winsock2.h>
// #include <ws2tcpip.h>
int main()
{
    char a[20], b[20];
    int k;
    int sock_desc;
    struct sockaddr_in server;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
        printf("error in socket");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = 3003;

    k = connect(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
        printf("error in connecting");

    printf("enter first number :");
    fgets(a, 20, stdin);
    k = send(sock_desc, a, strlen(a), 0);
    if (k == -1)
        printf("error in sending");

    printf("enter second number :");
    fgets(b, 20, stdin);
    k = send(sock_desc, b, strlen(b), 0);

    close(sock_desc);
    return 0;
}