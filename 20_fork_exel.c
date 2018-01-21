#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    pid_t child;
    int status;

    child = fork();
    if (child == 0) {
        execl("/bin/ls", "/tmp/",NULL);
    } else if (child > 0) {
		getchar(); //Check for zombie 
        wait(&status);
    }
    return 0; 
	
}    


