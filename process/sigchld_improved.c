#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void foo() {
    pid_t pid = getpid();
    int i;

    for (i=0; i<5; i++) {
        printf("Child: %d, count = %d\n", pid, i);
        sleep(1);
    }
}

void reap_child(int signum) 
{
    int status;
    pid_t pid;

    pid = wait(&status);
    printf("Reaped child process: %d\n", pid);

}


int main ()
{
    pid_t child_pid;
    struct sigaction act, old_act;
    int i;

	/*Why following flags are required? 
	  a) If parent is not interested in return value of child when it exits
		 Or when it is STOPPED

			SA_NOCLDWAIT:	
				Do not transform children into zombies when they terminate
			SA_NOCLDSTOP:
				 If signum is SIGCHLD, do not receive notification when child stops
	*/	
    act.sa_flags =  SA_NOCLDSTOP | SA_NOCLDWAIT;
    act.sa_handler = reap_child;

    sigaction(SIGCHLD, &act, &old_act); 

    for (i=0; i<10; i++) {
        child_pid = fork();
        if (child_pid == 0) {
            foo();
            exit(0);
        } else {
            printf("Parent: created child process: %d\n", child_pid);
        }
     }

     i = 0;
     while (1) {
         //printf("In parent: count = %d\n", ++i);
         sleep(5);
     }

     return 0;
}
