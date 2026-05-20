#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    char buf[3][100];
    char ack[2];
    int i = 1, k;
    int sock_desc, conn_fd;
    struct sockaddr_in server, client;
    socklen_t len;

    // 1. Create TCP socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        printf("error in socket creation.\n");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    k = bind(sock_desc, (struct sockaddr*)&server, sizeof(server));
    if (k < 0) {
        printf("error in binding.\n");
    }

    // 2. listen() — marks socket as passive, waiting for connections
    listen(sock_desc, 1);
    printf("waiting for client...\n");

    // 3. accept() — blocks until a client connects, returns a new socket for this connection
    len = sizeof(client);
    conn_fd = accept(sock_desc, (struct sockaddr*)&client, &len);
    if (conn_fd < 0) {
        printf("error in accepting connection.\n");
    }
    printf("client connected.\n");

    while (i < 4) {
        printf("\nreceiving packet %d\n", i);

        // 4. recv() on conn_fd (the per-client socket), not the listening socket
        k = recv(conn_fd, buf[i-1], 100, 0);
        if (k < 0) {
            printf("error in receiving.\n");
            break;
        }

        printf("packet %d data: %s\n", i, buf[i-1]);
        printf("ack for packet %d (1=ok, 0=resend): ", i);
        scanf("%1s", ack);

        // 5. send() on conn_fd
        k = send(conn_fd, ack, 1, 0);
        if (k < 0) {
            printf("error in sending ack.\n");
            break;
        }
        printf("ack sent: %s\n", ack);

        if (strcmp(ack, "1") == 0) {
            i++;
        }
    }

    printf("\nall packets received:\n");
    for (i = 0; i < 3; i++) {
        printf("%s\n", buf[i]);
    }

    close(conn_fd);
    close(sock_desc);
    return 0;
}