#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    char a[100],b[100];
    int k;
    int sock_descriptor;
    struct sockaddr_in server;  // import server details
    sock_descriptor = socket(AF_INET,SOCK_STREAM,0);  // creating socket(version,to show tcp,tcpip so 0)
    if(sock_descriptor == -1)
          printf("Error in socket creation!\n");
    server.sin_family = AF_INET;     // server family
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  //server address
    server.sin_port = 3003; //port address
    k = connect(sock_descriptor,(struct sockaddr*)&server,sizeof(server)); //connect the server
    if(k == -1)
         printf("Error in connecting to server\n");
    printf("Enter first number:");
    fgets(a,sizeof(a),stdin);   //to overcome buffer overflow
    k = send(sock_descriptor,a,strlen(a),0);
    if(k== -1)
        printf("Error in sending\n");
        
    printf("Enter second number:");
    fgets(b,sizeof(b),stdin);   //to overcome buffer overflow
    k = send(sock_descriptor,b,strlen(b),0);
    if(k == -1)
        printf("Error in sending\n");
        
    close(sock_descriptor);
    return 0;
}
