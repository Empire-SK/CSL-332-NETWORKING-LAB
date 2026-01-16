#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
void check(char strr[], int value){
  if (value < 0){
    perror(strr);
    exit(1);
  }
  }
int main(){
  int sid, sbind, slisten, saccept, srec, ssend, size;
  char recbuff[500], sendbuff[500], fromaddress[500], toaddress[500], mailbody[1000];
  struct sockaddr_in saddr, caddr;
  sid = socket(AF_INET, SOCK_STREAM, 0);
  check("SOCKET CREATION", sid);
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(8082);
  saddr.sin_addr.s_addr = INADDR_ANY;
  size = sizeof(struct sockaddr_in);
  sbind = bind(sid, (struct sockaddr *)&saddr, size);
  check("BINDING", sbind);
  slisten = listen(sid, 5);
  check("LISTEN", slisten);
  printf("Server listening on port 8082...\n");
  saccept = accept(sid, (struct sockaddr *)&caddr, (socklen_t*)&size);
  check("ACCEPT", saccept);
  printf("\nClient Connected.\n");

  srec = recv(saccept, recbuff, 500, 0);
  check("RECEIVE", srec);
  printf("Message from client: %s\n", recbuff);
  printf("Sending response for HI..\n");
  strcpy(sendbuff, "220 192.168.9.138");
  ssend = send(saccept, sendbuff, 500, 0);
  check("SENDING", ssend);

  printf("Waiting for client response..\n");
  srec = recv(saccept, recbuff, 500, 0);
  check("RECEIVE", srec);
  if(strncmp(recbuff, "HELLO", 5) != 0)
    printf("Error: Expected HELLO\n");
  else
    printf("Message from client: %s\n", recbuff);
  printf("Sending response for HELLO..\n");
  strcpy(sendbuff, "250 OK");
  ssend = send(saccept, sendbuff, 500, 0);
  check("SENDING", ssend);

  srec = recv(saccept, fromaddress, 500, 0);
  check("RECEIVE", srec);
  if (strncmp(fromaddress, "MAIL FROM:", 10) != 0)
    printf("From address error\n");
  else
    printf("From address: %s\n", fromaddress);
  printf("Sending OK to FROM address\n");
  strcpy(sendbuff, "250 OK");
  ssend = send(saccept, sendbuff, 500, 0);
  check("SENDING", ssend);

  printf("Waiting for TO address\n");
  srec = recv(saccept, toaddress, 500, 0);
  check("RECEIVE", srec);
  if(strncmp(toaddress, "MAIL TO:", 8) != 0)
    printf("To address error\n");
  else
    printf("To address: %s\n", toaddress);  
  printf("Sending OK to TO address\n");
  strcpy(sendbuff, "250 OK");
  ssend = send(saccept, sendbuff, 500, 0);
  check("SENDING", ssend);

  printf("Waiting for DATA\n");
  srec = recv(saccept, recbuff, 500, 0);  
  check("RECEIVE", srec);
  if(strncmp(recbuff, "DATA", 4) != 0)
    printf("Data not received\n");
  else
  printf("Message from client: %s\n", recbuff);
  printf("Sending GO AHEAD to client\n");
  strcpy(sendbuff, "354 GO AHEAD");
  ssend = send(saccept, sendbuff, 500, 0);
  check("SENDING", ssend);

  printf("Mail body:\n");
  while (1){
    srec = recv(saccept, mailbody, 1000, 0);
    check("MAIL BODY RECEIVE", srec);
  if(strncmp(mailbody, "$", 1) == 0)
    break;
  else
    printf("%s", mailbody);}
  strcpy(sendbuff, "221 OK");
  ssend = send(saccept, sendbuff, 500, 0);
  printf("Sending OK to client (Body received)\n");
  check("SENDING", ssend);

  srec = recv(saccept, mailbody, 1000, 0);
  if(strncmp(mailbody, "QUIT", 4) == 0){
  strcpy(sendbuff, "221 OK");
  ssend = send(saccept, sendbuff, 500, 0);
  printf("Sending 221 OK for QUIT...\n");
  }
  printf("Connection closed\n");
  close(saccept);
  close(sid);
  return 0;
}
