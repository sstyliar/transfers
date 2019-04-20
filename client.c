#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//</da inludings>

//random ass defines in the wild...dont look it in da eyes
#define SIZE 1024
//structs
typedef struct 
{  
  char username[50];
  char msg[SIZE];
  int sock;
  int id;
}client;

//initers
client clientInit(client newClient){

  strcpy(newClient.username, "C sucks");
  strcpy(newClient.msg, "Handshake yo");
  newClient.id = 0;
  return newClient;
}


//the core magic 
void mainControler(int sock){
  int start =1;
  char name[50], tempMsg[SIZE];
  client newClient = clientInit(newClient);
  newClient.sock = sock;
  //at this point we have a struct with default name and msg and the sock
  printf("Tell me your deepest darkest secrets...or just your name\n");
  fgets(name, sizeof name, stdin);
  strcpy(newClient.username, name);

  //send to the server and initiate handshake (say hi :p)
  send(sock, &newClient, sizeof(client), 0);
  recv(sock, &newClient, sizeof(client), 0);
  

  printf("Server said: %s\n", newClient.msg);
  printf("Server set your id to: %d\n\n", newClient.id);

  do{
    printf("Wanna share something?...really, anything...: ");
    strcpy(newClient.msg, ""); //clear the msg (maybe too much...but i have ocd anyways)
    fgets(tempMsg, sizeof tempMsg, stdin);
    strcpy(newClient.msg, tempMsg);

    tempMsg[strcspn(tempMsg, "\n")] = 0;
    if(strcmp(tempMsg, "cya") != 0){
      send(sock, &newClient, sizeof(client), 0);
    }
    else{
      send(sock, &newClient, sizeof(client), 0);
      break;
    }

  }
  while(1);
}


//why are developers bad at league?
//
//
//Cause the main ints....haha xD( send help!! )
int main(int argc, char *argv [])
{
  system("clear");
  //<initial stuff>
  int sock, i ;
  char msg[SIZE], name[50];
  struct sockaddr_in addr; // Internet socket
  addr.sin_family = AF_INET; // Internet socket
  //  inet_aton(argv[1], &addr.sin_addr);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_port = htons(atoi("909091") ) ;
  sock = socket(AF_INET, SOCK_STREAM, 0); // Stream socket
  connect(sock, (struct sockaddr *)&addr, sizeof(addr));
  //</initial stuff>

  //pass variables to main controller to handle logic
  mainControler(sock);

  close(sock);
  return 0;
}