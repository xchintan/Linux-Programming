/* UNIX Domain socket for IPC */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>


void handle_connection(int client)
{
     char buffer[256]="";
     ssize_t n;


     while (1) {
        n = read(client, buffer, 255);
        if (0==n) 
			break;

        buffer[n] = '\0';
        printf("Client says: %s\n",buffer);

        n = write(client, "I got your message", 18);
    }
    close(client);
}

int main(int argc, char *argv[])
{
     int sock_fd, client_sock;
	 int portno, clilen;

     struct sockaddr_un  serv_addr={0};
	 struct sockaddr_un  cli_addr={0};
     int n;
     pid_t pid;

	 sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);

     serv_addr.sun_family = AF_UNIX;
     strcpy(serv_addr.sun_path, "xmydata.sock");


     bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
     listen(sock_fd, 5);

     while (1) {
         client_sock = accept(sock_fd, (struct sockaddr *) &cli_addr, &clilen);
         pid = fork();
         if (pid == 0) {
            handle_connection(client_sock);
            exit(0);
         }
    }

     return 0; 
}
