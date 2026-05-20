#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    char buf[3][100] = {
        "i am batman.",
        "i am the protector of gotham.",
        "i am walter white."
    };
    char ack[2];  // +1 for null terminator
    int i = 1, k;
    int sock_desc;
    struct sockaddr_in server;

    // 1. Create TCP socket (SOCK_STREAM instead of SOCK_DGRAM)
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        printf("error in socket.\n");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(3003);  // htons() for correct byte order

    // 2. connect() establishes the connection (TCP handshake)
    k = connect(sock_desc, (struct sockaddr*)&server, sizeof(server));
    if (k < 0) {
        printf("error in connecting to server.\n");
        return 1;
    }

    printf("connected to server.\n");

    while (i < 4) {
        printf("\nsending packet %d\n", i);

        // 3. send() instead of sendto() — no address needed (connection is established)
        k = send(sock_desc, buf[i-1], 100, 0);
        if (k < 0) {
            printf("error in sending.\n");
            break;
        }

        printf("waiting for ack...\n");

        // 4. recv() instead of recvfrom()
        k = recv(sock_desc, ack, 1, 0);
        if (k < 0) {
            printf("error in receiving.\n");
            break;
        }

        ack[1] = '\0';  // null-terminate for safe strcmp
        printf("ack received: %s\n", ack);

        if (strcmp(ack, "1") == 0) {
            i++;
        } else {
            printf("resend needed for packet %d.\n", i);
        }
    }

    close(sock_desc);
    return 0;
}