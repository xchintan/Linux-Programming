/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
     int  sockfd, client_sock;
	 int  port = {0};
     int n;

     char buffer[256] = "";
     struct sockaddr_in serv_addr = {0};
	 struct sockaddr_in cli_addr = {0};

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

	//Open a TCP Connetion
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Prepare sock addr
     port = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(port);

	//Bind
     bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));

	//Listen
     listen(sockfd,5);


	 //Accept Blocking call
     client_sock = accept(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
		
	 //Read from the client
     n = read(client_sock,buffer,255);
     printf("Client says: %s\n",buffer);

	 //Send a reply
     n = write(client_sock,"I got your message",18);
     return 0; 
}
