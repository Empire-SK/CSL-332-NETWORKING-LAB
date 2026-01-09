#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    FILE *fp;
    int sd, newsd, port, n, a;
    socklen_t clilen;
    char fileread[100], rcv[100];
    struct sockaddr_in servaddr, cliaddr;
    printf("Enter the port address: ");
    scanf("%d", &port);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
        printf("Can't create socket\n");
    else
        printf("Socket is created\n");
    int opt = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    a = sizeof(servaddr);
    if (bind(sd, (struct sockaddr *)&servaddr, a) < 0) {
        printf("Can't bind (Port might be busy)\n");
        exit(1);
    }else{
        printf("Binded\n");
    }
    listen(sd, 5);
    clilen = sizeof(cliaddr);
    printf("Waiting for connection...\n");
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);    
    if(newsd < 0){
        printf("Can't accept\n");
        exit(1);
    }else{
        printf("Accepted connection\n");
    }
    memset(rcv, 0, sizeof(rcv));
    n = recv(newsd, rcv, sizeof(rcv) - 1, 0);
    if(n > 0){
        rcv[n] = '\0'; 
        printf("Client requested file: %s\n", rcv);
        fp = fopen(rcv, "r");
        if (fp == NULL) {
            printf("File not found.\n");
            send(newsd, "error", 5, 0);
        } 
        else{ 
            while(fgets(fileread, sizeof(fileread), fp) != NULL) {
             if (send(newsd, fileread, strlen(fileread), 0) < 0) {
                    printf("Error sending file content\n");
                    break;
                }
            }
            sleep(1); 
            send(newsd, "end", 3, 0);
            printf("File transfer completed.\n");
            fclose(fp);
        }
    }else{
        printf("Error receiving filename\n");
    }
    close(newsd);
    close(sd);
    return 0;
}
