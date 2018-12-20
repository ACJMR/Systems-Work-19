#include "pipe_networking.h"

static void sighandler(int signo){
  if (signo == SIGINT) {
    remove("to_server");
    exit(0);
  }
}

int main() {
  signal(SIGINT,sighandler);
  int to_client;
  int from_client;

  while(1){
    from_client = server_handshake( &to_client );
    while(1){
      char message[BUFFER_SIZE];
      int p = read(from_client,message,BUFFER_SIZE);

      if(!p){
        break; //if client not there, handshake again
      }

      int i = 0;
      while(message[i]){
        message[i] = toupper(message[i]);
        i++;
      }

      write(to_client,message,BUFFER_SIZE);
    }
  }

}
