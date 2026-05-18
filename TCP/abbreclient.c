#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    char str[100], result[100];
    int k;
    int sock_desc;
    struct sockaddr_in server;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) 
        printf("Error in socket\n");

    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port        = htons(3003);       // ← must match server

    k = connect(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1) 
        printf("Error in connecting\n"); 
    // Send the phrase to abbreviate
    printf("Enter a phrase: ");
    fgets(str, sizeof(str), stdin);

    k = send(sock_desc, str, strlen(str), 0);
    if (k == -1) 
        printf("Error in sending\n"); 

    // Receive the abbreviation back
    k = recv(sock_desc, result, sizeof(result) - 1, 0);
    if (k == -1) 
        printf("Error in receiving\n");
    result[k] = '\0';

    printf("Abbreviation: %s\n", result);

    close(sock_desc);
    return 0;
}