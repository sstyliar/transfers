#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//</da inludings>

//random ass defines in the wild...dont look it int da eye
#define SIZE 1024
//structs
typedef struct 
{  
  char username[50];
  char msg[SIZE];
  int sock;
}client;

//initers
client clientInit(client newClient){

  strcpy(newClient.username, "C sucks");
  strcpy(newClient.msg, "");
  return newClient;
}


//the core magic 
void mainControler(client *newClient, int sock){
  int start =1;
  do{
    if(start == 1){
      start = 0;
      //say hello to the server
      //aka #handshake
      send(sock, &newClient, sizeof(client), 0);
      recv(sock, &newClient, sizeof(client), 0);
      printf("server said hello this msg: %s", newClient->msg);
    }
    else{
      
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
  //init new client
  client newClient = clientInit(newClient);
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

  printf("Tell me your deepest darkest secrets...or just you name\n");
  fgets(name, sizeof name, stdin);
  strcpy(newClient.username, name);
  //pass variables to main controller to handle logic
  mainControler(&newClient, sock);


  //  printf("\nWanna tell me a secret?");
  //  printf("\n .\n .\n .\n .\n .\nPromise i wont tell it to anyone :)\n");
  //
  //  do{
  //    if (fgets(msg, sizeof msg, stdin)) {
  //      if (strcmp(msg, "\n")){
  //        printf ("IM TELLING EVERYONE...: %s\n", msg);
  //        send(sock, msg, strlen(msg) + 1, 0) ;  
  //        strcpy(msg, "") ;
  //        printf("Tell me more...  ");
  //      }
  //      else{
  //        printf("\ncome again soon <3\n");
  //        break;
  //      }
  //    }
  //    else{
  //      printf("Error in fgets func...");
  //    }
  //  }while(1);

  close(sock);

  return 0;
}