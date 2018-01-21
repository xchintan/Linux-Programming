#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

struct sigaction old_act;
struct sigaction act;

void sighandler(int signum) 
{
    printf("Received signal %d\n", signum);
    printf("I'll not get the second chance \n");

	//Restore the old signal handler
    sigaction(SIGINT, &old_act, NULL);
}

int main() 
{
	printf("pid = %d\n",getpid());

	memset(&act,0,sizeof(sigaction));
	memset(&old_act,0,sizeof(sigaction));

	act.sa_handler = sighandler;
	sigaction(SIGINT,&act,&old_act);
	
	while(1) {
		sleep(5);
		printf("Doing some stuff\n");
	}
	return 0;

}


