#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
  pid_t child_pid;
  printf("Zombie Child: Parent has not reapped the dying child\n");

  child_pid = fork();
  if (child_pid > 0) {
	  printf("In parent: child =\t%u\n", child_pid);
	  printf("In parent: pid =\t%u\n", getpid());
	  printf("Press any key to exit \n");
	  getchar();
  } else if (child_pid == 0) {
	  printf("child is exiting...\n");
	  exit(10);
  }
  
  return 0;
}
