#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024
int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    int num1, num2, result;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("server listening on port %d..\n", SERVER_PORT);
    while (1)
    {
        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (structsockaddr *)&client_addr, &addr_len);
        if (recv_len < 0)
        {
            perror("Recvfrom failed");
            continue;
        }
        buffer[recv_len] = '\0';
        if (sscanf(buffer, "%d%d", &num1, &num2) == 2)
        {
            result = num1 + num2;
            printf("received number: %d & %d\n", num1, num2);
            printf("result: %d\n", result);
        }
        else
        {
            printf("invalid input.please send two integers\n");
        }
    }
    close(sockfd);
    return 0;
}