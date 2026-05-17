#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = {AF_INET, htons(8080), INADDR_ANY};
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    bind(sock, (struct sockaddr*)&server, sizeof(server));
    printf("Server listening on port 8080...\n");

    // Receive message and the client's address
    int n = recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&client, &len);
    buffer[n] = '\0';
    printf("Client says: %s\n", buffer);

    return 0;
}
