#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#define CAPACITY 10

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void handle_connection(int client) 
{
    char buf[256];
    int n;

    while (1) {
        bzero(buf, 256);
        n = read(client, buf, 255);
        if (n == -1) {
            perror("read");
            break;
        } else if (n == 0) {
            break;
        }

        buf[n] = '\0';
        
        if (strcmp(buf, "bye\n") == 0) 
            break;

        printf("Got message: %s\n", buf);
        n = write(client, buf, n);
        if (n == -1) {
            perror("write");
            break;
        }
    }
    close(client);
}

void poll_connection(int listener)
{
    int clilen, client;
    struct sockaddr_un cli_addr;

    while (1) {
        clilen = sizeof(cli_addr);
        bzero((char *) &cli_addr, sizeof(cli_addr));

        if ((client = accept(listener, (struct sockaddr *) &cli_addr, &clilen)) == -1) {
            perror("accept");
            continue;
        }
        handle_connection(client);
   }

}


int main(int argc, char *argv[])
{
     int listener, client, portno, clilen;
     char buffer[256];
     struct sockaddr_un serv_addr, cli_addr;
     int n, i;
     int ret;
     pid_t worker[CAPACITY];

     listener = socket(AF_UNIX, SOCK_STREAM, 0);
     if (listener < 0) 
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sun_family = AF_UNIX;
     strcpy(serv_addr.sun_path, "echoserver.sock");


     if (bind(listener, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
              error("ERROR on binding");

     listen(listener, 16384);

     for (i=0; i<CAPACITY; i++) {
         worker[i] = fork();
         if (worker[i] == 0) {
             poll_connection(listener);
             exit(0);
         }
    }



     return 0; 
}
