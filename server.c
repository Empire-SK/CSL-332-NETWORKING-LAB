#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
 char a[100],b[100],sum1[100];
 int m=0,n=0,sum=0;
 int k;
 
 socklen_t len;
 int sock_descriptor,temp_sock_descriptor;
 struct sockaddr_in server,client;  // import server details
 sock_descriptor = socket(AF_INET,SOCK_STREAM,0);  // creating socket(version,to show tcp,tcpip so 0)
 if(sock_descriptor == -1)
          printf("Error in socket creation!\n");
 server.sin_family = AF_INET;     // server family
 server.sin_addr.s_addr = inet_addr("127.0.0.1");  //server address
 server.sin_port = 3003; //port address
 k = bind(sock_descriptor,(struct sockaddr*)&server,sizeof(server));
 if(k == -1)
      printf("Error in binding\n");
 k= listen(sock_descriptor,5);
  if(k == -1)
      printf("Error in listening\n");
 len=sizeof(client);
 temp_sock_descriptor = accept(sock_descriptor,(struct sockaddr*)&client,&len);
 if(temp_sock_descriptor == -1 )
     printf("error in temporary socket creation\n");
     
 k = recv(temp_sock_descriptor,a,strlen(a),0);
  if(k == -1)
      printf("Error in receiving\n");
  m = atoi(a);
 
  k = recv(temp_sock_descriptor,b,strlen(b),0);
  if(k == -1)
      printf("Error in receiving\n");
  n = atoi(b);
  sum = m + n;
  sprintf(sum1,"%d",sum);
  printf("sum = %s\n",sum1);
  
  close(temp_sock_descriptor);
  return 0;
 
 }
