/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
     int sock_fd;
     char buffer[256]="";
     char buf[256]="";
     struct sockaddr_un serv_addr = {0};
     int n;

     sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);

     serv_addr.sun_family = AF_UNIX;
     strcpy(serv_addr.sun_path, "xmydata.sock");

     connect(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
     while (1) {
        n = read(0, buf, 255); //Read from stdin
        buf[n] = '\0';
        write(sock_fd, buf, n);
        if (!n) {
            break;
        }
     }
     close(sock_fd);
     return 0; 
}
