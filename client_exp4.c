#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    FILE *fp;
    int csd, n, cport;
    char name[100], rcvmsg[100], fname[100];
    struct sockaddr_in servaddr;
    printf("Enter the port: ");
    scanf("%d", &cport);
    csd = socket(AF_INET, SOCK_STREAM, 0);
    if(csd < 0){
        printf("Error....\n");
        exit(0);
    }else{
        printf("Socket is created\n");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(cport);
    if (connect(csd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Error in connection\n");
        exit(1);
    }else{
        printf("Connected\n");
    }
    printf("Enter the existing file name to fetch: ");
    scanf("%s", name);
    printf("Enter the new file name to save as: ");
    scanf("%s", fname);
    send(csd, name, strlen(name), 0);
    fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        close(csd);
        exit(1);
    }while (1){
        memset(rcvmsg, 0, sizeof(rcvmsg));
        n = recv(csd, rcvmsg, sizeof(rcvmsg) - 1, 0);
        if (n <= 0) {
            break; 
        }
        rcvmsg[n] = '\0'; 
        if (strcmp(rcvmsg, "error") == 0) {
            printf("File is not available on server.\n");
            fclose(fp);
            remove(fname); 
            close(csd);
            exit(1);
        }if (strcmp(rcvmsg, "end") == 0) {
            printf("\nFile transferred successfully.\n");
            fclose(fp);
            close(csd);
            exit(0);
        }
        printf("%s", rcvmsg);
        fprintf(fp, "%s", rcvmsg);
    }
    fclose(fp);
    close(csd);
    return 0;
}
