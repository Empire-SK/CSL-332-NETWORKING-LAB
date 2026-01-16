#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void check(char strr[],int value){
  if (value<0){
  perror(strr);
  exit(1);
  }
  }
int main(){
  int cid,con,csend,crec;
  char sendbuff[500],recbuff[500],fromaddress[500],toaddress[500],mailbody[1000];
  struct sockaddr_in caddr;
  cid=socket(AF_INET,SOCK_STREAM,0);
  check("Socket creation",cid);
  caddr.sin_family=AF_INET;
  caddr.sin_port=htons(8082);
  caddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  con=connect(cid,(struct sockaddr*)&caddr,sizeof(caddr));
  check("CONNECTION",con);
  printf("\n<-->CONNECTION ESTABLISHED<-->\n");
  
  printf("Sending HI to server\n");
  strcpy(sendbuff,"HI");
  csend=send(cid,sendbuff,500,0);
  check("SENDING",csend);
  printf("Waiting for server response..\n");
  crec=recv(cid,recbuff,500,0);
  check("RECEIVE",crec);
  printf("Message from server:%s\n",recbuff);
  
  printf("Sending HELLO to server\n");
  strcpy(sendbuff,"HELLO");
  csend=send(cid,sendbuff,500,0);
  check("SENDING",csend);
  printf("Waiting for OK message..\n");
  crec=recv(cid,recbuff,500,0);
  check("RECEIVE",crec);
  if(strncmp(recbuff,"250",3)!=0)
    printf("OK not received\n");
  else
    printf("Message from server:%s\n",recbuff);
    
  printf("Enter the FROM address:");
  scanf("%s",fromaddress);
  strcpy(sendbuff,"MAIL FROM:");
  strcat(sendbuff,fromaddress);
  csend=send(cid,sendbuff,500,0);
  check("SENDING",csend);
  printf("Waiting OK from server\n");
  crec=recv(cid,recbuff,500,0);
  check("RECEIVE",crec);
  if(strncmp(recbuff,"250",3)!=0)
    printf("OK not received\n");
  else
    printf("Message from server:%s\n",recbuff);
    
  printf("Enter TO address:");
  scanf("%s",toaddress);
  getchar();
  strcpy(sendbuff,"MAIL TO:");
  strcat(sendbuff,toaddress);
  csend=send(cid,sendbuff,500,0);
  check("SENDING",csend);
  printf("Waiting OK from server\n");
  crec=recv(cid,recbuff,500,0);
  check("RECEIVE",crec);
  if(strncmp(recbuff,"250",3)!=0)
    printf("OK not received\n");
  else
    printf("Message from server:%s\n",recbuff);
    
  printf("Sending data to the server:");
  strcpy(sendbuff,"DATA");
  csend=send(cid,sendbuff,500,0);
  check("SENDING",csend);
  printf("Waiting OK from server\n");
  crec=recv(cid,recbuff,500,0);
  check("RECEIVE",crec);
  if(strncmp(recbuff,"354",3)!=0)
    printf("OK not received\n");
  else
    printf("Message from server:%s\n",recbuff);
    
  printf("Enter mail body (Type '$' on a new line to finish):\n");
  while(1){
    fgets(mailbody,sizeof(mailbody),stdin);
    csend=send(cid,mailbody,1000,0);
    check("SENDING",csend);
    if(strncmp(mailbody,"$",1)==0)
      break;
    }
  printf("Waiting OK from server\n");
  crec=recv(cid,recbuff,500,0);
  check("RECEIVE",crec);
  if(strncmp(recbuff,"221",3)!=0)
    printf("OK not received\n");
  else
    printf("Message from server:%s\n",recbuff);
    
  strcpy(sendbuff,"QUIT");
  csend=send(cid,sendbuff,1000,0);
  printf("Sending %s..\n",sendbuff);
  strcpy(recbuff,"");
  crec=recv(cid,recbuff,500,0);
  if(strncmp(recbuff,"221 OK",6)==0){
    printf("Exiting..\n");
    }
  printf("Connection closed\n");
  close(cid);
  return 0;
  }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  
