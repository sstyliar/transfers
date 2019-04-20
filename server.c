#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   
#include <pthread.h>

#define SIZE 1024
#define port 909091
//structs
typedef struct 
{  
  char username[50];
  char msg[SIZE];
  int sock;
}client;

int getRandom(){
  srand((unsigned int)time(NULL));  
  int r = rand(); 
  return r;
}

//init vars...most of them will be changed later...
client clientInit(client *newClient){
  strcpy(newClient->username, "Vasoula send nudes");
//  newClient->id = getRandom();
  strcpy(newClient->msg, "");
  newClient->sock = 0;
  return *newClient;
} 

void *mainControler(void *socket)
{
  client *client;
//  strcpy(client->username, "Vasoula send nudes");
//  strcpy(client->msg, "");
//  client->firstConnect = 1;
  client->sock = *(int*)socket;
  recv(client->sock, &client, sizeof(client), 0);
  strcpy(client->msg, "hi...welcome to the club");
  send(client->sock, &client, sizeof(client), 0);
  

  close(client->sock);
  return 0;
}

int main(int argc, char *argv [])
{
  char msg[SIZE];
  //<socket stuff>
  int psock, client_sock, c, i=0; 
  struct sockaddr_in serv_addr , client;

  struct sockaddr_in addr; // Internet socket
  addr.sin_family = AF_INET; // Internet socket
  addr.sin_addr.s_addr = htonl(INADDR_ANY); // All interfaces
  addr.sin_port = htons(atoi("909091") ) ;
  if((psock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    printf("Failed creating socket\n");
  bind(psock, ( struct sockaddr *)&addr, sizeof(addr));
  listen (psock, 3) ;
  //</socket stuff>

  //init stuff
  system("clear");  
  printf("Waiting for new connection...\n") ;
  c = sizeof(struct sockaddr_in);
  pthread_t thread_id;


  while((client_sock = accept(psock,NULL, NULL)))
  {
    printf("Connection established...\n") ;
    if( pthread_create( &thread_id, NULL , mainControler , (void*) &client_sock) < 0)
    {
      perror("could not create thread...rigga we fuc***d up");
      return 1;
    }
    i++;
    if (i == 3)
    {
      break;
    }

  }
  pthread_join(thread_id, NULL);
  printf ("Connection closed...\n") ;
  sleep(2);
  close(psock);
  unlink(argv [1]);
  system("clear");
  return 0;

}









//  
//  strcpy(msg, "") ;
//  while (strcmp(msg, "exit") != 0) {
//    printf ("\nnobody loves me yet i quess...do you? :(\n") ;
//
//    sock = accept(psock, NULL, NULL);
//
//    printf ("yayyyyyyyy\n") ;
//
//    recv(sock, msg, SIZE, 0) ;
//
//    if (strcmp(msg, "exit") != 0) {
//      printf ("running command : [%s]\n", msg);
//      system(msg);
//    }
//    close(sock);
//    printf ("\nconnection closed...\n") ;
//  }
//
//  close(psock);
//  unlink(argv [1]) ;
//
//  return 0;
//}
