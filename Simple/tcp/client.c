#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define IP   "127.0.0.1"

int main() {
    char buf[1024];

    // 1. Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Set server address
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(PORT)
    };
    inet_pton(AF_INET, IP, &addr.sin_addr);

    // 3. Connect
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));

    // 4. Send/Receive loop
    while (1) {
        memset(buf, 0, sizeof(buf));          // clear buffer each iteration
        printf("Enter: ");
        fgets(buf, sizeof(buf), stdin);

        send(sock, buf, strlen(buf), 0);

        if (strcmp(buf, "exit\n") == 0) break;

        memset(buf, 0, sizeof(buf));          // clear before receiving
        recv(sock, buf, sizeof(buf), 0);
        printf("Reversed: %s\n", buf);
    }

    close(sock);
    return 0;                                 // was missing
}
