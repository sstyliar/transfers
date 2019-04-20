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
pthread_t thread_id[3];

//structs
typedef struct 
{  
  char username[50];
  char msg[SIZE];
  int sock;
  int id;
}client;

//returns a random number used for id(ing) the new connection
int getRandom(){
  srand(time(0));
  int r = rand()%100; 
  return r;
}

//init vars...most of them will be changed later...
void clientInit(client *newClient){
  strcpy(newClient->username, "Vasoula send nudes");
  strcpy(newClient->msg, "Haven't had sex in 4 months...send help");
  newClient->sock = 0;
  newClient->id = 0; 
} 
void setId(client *newClient){
  newClient->id = getRandom(); 
}
void setupWelcome(client *clientEcho){
  char temp[50];
  strcpy(temp, "hi ");
  strcat(temp, clientEcho->username);
  strcpy(clientEcho->msg, temp);
}

void *mainControler(void *socket)
{
  char welcome[50], tempMsg[SIZE];
  client clientEcho ;
  clientInit(&clientEcho);
  recv(*(int*)socket, &clientEcho, sizeof(client), 0);
  printf("Recieved from client: %s\n", clientEcho.msg); //handshake
  setupWelcome(&clientEcho);
  setId(&clientEcho);
  send(*(int*)socket, &clientEcho, sizeof(clientEcho), 0);

  //infinite loop...base logic
  do{ 
      recv(*(int*)socket, &clientEcho, sizeof(client), 0);
      strcpy(tempMsg, clientEcho.msg);
      tempMsg[strcspn(tempMsg, "\n")] = 0;
      if(strcmp(tempMsg, "cya") != 0){
        printf("\nRecieved from client with id{%d}: %s",clientEcho.id, clientEcho.msg);
      }
      else{
        close(clientEcho.sock);
        printf("\n\tClient %n logged out.\n", clientEcho.id);
        int ret1  = 100;
        break;
      };

  }while(1);
  int ret1 = 100;
  pthread_exit(&ret1);
  printf("check");
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
  //</socket stuff>

  //small check to see if we utterly suck at life
  if((psock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("Failed creating socket\n");
  }
  bind(psock, ( struct sockaddr *)&addr, sizeof(addr));
  listen (psock, 3) ;
  

  //init stuff
  system("clear");  
  printf("Waiting for new connection...\n") ;
  c = sizeof(struct sockaddr_in);
  
  while(1){
    if((client_sock = accept(psock,NULL, NULL)) == -1){
      printf("Could not accept() connection");
    }
    if( pthread_create( &thread_id[i], NULL , &mainControler , (void*) &client_sock) < 0)
    {
      perror("could not create thread...rigga we fuc***d up");
      return 1;
    }
     i++;
  }



  while(client_sock = accept(psock,NULL, NULL))
  {
    printf("Connection established...\n") ;
    if( pthread_create( &thread_id[i], NULL , &mainControler , (void*) &client_sock) < 0)
    {
      perror("could not create thread...rigga we fuc***d up");
      return 1;
    }
    i++;
  }
  sleep(5);
  pthread_join(thread_id[0], NULL);
  pthread_join(thread_id[1], NULL);
  pthread_join(thread_id[2], NULL);
  printf ("Connection closed...\n") ;
  close(psock);
  unlink("909091");
  return EXIT_SUCCESS;
}