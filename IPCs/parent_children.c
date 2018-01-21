#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{

	int fd[2];
	int status;
	pid_t c1, c2;
	if (pipe(fd) == -1) {
		perror("error");
		return -1;
	}

	c1 = fork();
	if(0==c1) {
		//Child-1 Producer
		close(fd[0]); // Close Read end
		dup2(fd[1],STDOUT_FILENO);
		execlp("/bin/ls", "-1", "/etc/", NULL);
	}
	/*Skipping all error checkings*/
	else {
		c2 = fork();
		if(0==c2) {
			//Consumer - Close the write end
			close(fd[1]);
			dup2(fd[0],STDIN_FILENO);
			execlp("/usr/bin/wc", "-lc", NULL); 

		}
	}

	//Each process must close reader and writer ends
	close(fd[0]);
	close(fd[1]);

    waitpid(c1, &status, 0);
    printf(">>> child1 exited.\n");

    waitpid(c2, &status, 0);
    printf(">>> child2 exited.\n");

    printf("Finished.\n");

	return 0;
}

