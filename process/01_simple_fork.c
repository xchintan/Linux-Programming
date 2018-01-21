#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  pid_t pid, wait_pid;
  int status;

  printf("pid = %d\n", getpid());
  printf("Press Any key to continue\n");
  getchar();

  pid  = fork();

	if (pid == 0) {
    	printf("child: pid =\t%d\n", getpid());
    	printf("child: ppid =\t%d\n", getppid());
    	sleep(2);
    	printf("child: exiting...\n");
		exit(100);
	} else if (pid > 0) {
	    printf("parent: pid =\t%d\n", getpid());
    	printf("parent: child =\t%d\n", pid);
	    wait_pid = wait(&status);
	    printf("parent: child %d exited with status: %d\n", 
				pid, WEXITSTATUS(status));
  } else {
    perror("fork");
  }

  return 0;
}
