#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr = {0};
    struct hostent *server= {0};

    char buffer[256];

	/*Parse the input*/
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);

	//Open a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Prepare sockaddr
    server = gethostbyname(argv[1]);
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
	
	//Connect to the server
    connect(sockfd,&serv_addr,sizeof(serv_addr));

	//get and send message
    printf("Please enter the message: ");
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
   
	//Read the message
	bzero(buffer,256);
    read(sockfd,buffer,32);
    printf("%s\n",buffer);

	close(sockfd);
    return 0;
}
