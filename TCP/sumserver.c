#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
int main()
{
    char a[100], b[100], sum1[100];
    int k;
    int m = 0, sum = 0, n = 0;
    socklen_t len;
    int sock_desc, temp_sock_desc;
    struct sockaddr_in server, client;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
        printf("Error in socketcreation");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
        printf("error in binding \n ");

    k = listen(sock_desc, 5);
    if (k == -1)
        printf("error in listening \n ");

    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (temp_sock_desc == -1)
        printf("error in temporary socket creation");

    k = recv(temp_sock_desc, a, 100, 0);
    if (k == -1)
        printf("ERROR in recieving");
    a[k] = '\0';
    m = atoi(a);

    k = recv(temp_sock_desc, b, 100, 0);
    if (k == -1)
        printf("ERROR in recieving");
    b[k] = '\0';
    n = atoi(b);

    sum = m + n;
    sprintf(sum1, "%d", sum);
    printf("SUM=%s\n", sum1);
    
    close(temp_sock_desc);
    return 0;
}