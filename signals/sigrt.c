#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>


void sig_handler(int signum, siginfo_t *info, void *ptr)
{
	printf("\tRcvd signal no: %d from pid = %d  Data = %d\n",
			signum, info->si_pid,info->si_int);	
	sleep(5);
	printf("\tSignal handler completed \n");
}

int main() 
{
	struct sigaction act;
	printf("pid = %d\n",getpid());
	printf("SIGRTMIN = %d   SIGRTMAX = %d\n",
			SIGRTMIN,SIGRTMAX);

	act.sa_sigaction = sig_handler;
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGRTMIN+1,&act,NULL);

	while(1) {
		printf("Doing some stuff\n");
		sleep(5);
	}
	return 0;
}

