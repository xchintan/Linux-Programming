#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

	int fd[2];
	pid_t pid;
	char buf[100];

	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}
	
	pid = fork();
	if (pid > 0) {
		close(fd[0]); /* close read end */
		sleep(5);
		write(fd[1], "hello world", 11);
		close(fd[1]);
	} else if (pid == 0) {
		close(fd[1]); /* close write end */
		read(fd[0], buf, 11);
		buf[11] = '\0';
		printf("Read data: %s\n", buf);
		close(fd[0]);
	}

	return 0;
}

