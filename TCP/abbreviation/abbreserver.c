#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void abbreviation(char str[], char abbr[]) {
    int i, j = 0;
    if (str[0] != ' ')
        abbr[j++] = toupper(str[0]);
    for (i = 1; str[i] != '\0'; i++)
        if (str[i-1] == ' ' && str[i] != ' ')
            abbr[j++] = toupper(str[i]);
    abbr[j] = '\0';
}

int main() {
    char a[100], abbr[100];
    int k;
    socklen_t len;
    int sock_desc, temp_sock_desc;
    struct sockaddr_in server, client;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) 
        printf("Error in socket creation\n");

    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port        = htons(3003);       // ← htons() is important!

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1) 
        printf("Error in binding\n");

    k = listen(sock_desc, 5);
    if (k == -1) 
        printf("Error in listening\n");

    printf("Server waiting for connection...\n");
    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (temp_sock_desc == -1) 
        printf("Error in accept\n");

    // Receive the string from the client
    k = recv(temp_sock_desc, a, sizeof(a) - 1, 0);
    if (k == -1) 
        printf("Error in receiving\n");
    a[k] = '\0';

    // Strip trailing newline if present (from fgets on client side)
    if (k > 0 && a[k-1] == '\n') a[k-1] = '\0';

    printf("Received string: \"%s\"\n", a);

    // Compute the abbreviation
    abbreviation(a, abbr);
    printf("Abbreviation: \"%s\"\n", abbr);

    // Send abbreviation back to the client
    k = send(temp_sock_desc, abbr, strlen(abbr), 0);
    if (k == -1) printf("Error in sending\n");

    close(temp_sock_desc);
    close(sock_desc);
    return 0;
}