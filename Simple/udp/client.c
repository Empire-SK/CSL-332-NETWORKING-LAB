#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = {AF_INET, htons(8080), inet_addr("127.0.0.1")};
    char message[1024],buffer[1024];

    printf("Enter message to send: ");
    fgets(message,1024,stdin);

    // Send message to server
    sendto(sock, message, strlen(message), 0, (struct sockaddr*)&server, sizeof(server));

    return 0;
}
