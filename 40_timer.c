#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>


void timer_handler(int signum, siginfo_t *sinfo, void *data)
{
	static count = 0;
	printf("[%d] Timer Handler Count: %d\n",
			sinfo->si_pid,count++);
	return;
}
int main()
{
	struct sigaction sa = {0};
	struct itimerval timer = {0};
	printf("pid = %d\n",getpid());
	
	sa.sa_sigaction = &timer_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGVTALRM, &sa, NULL);

 	/* Configure the timer to expire after 750 msec...  */
  	timer.it_value.tv_sec = 0;
 	timer.it_value.tv_usec = 250000*3;

  	/* ... and every 750 msec after that.  */
 	timer.it_interval.tv_sec = 0;
  	timer.it_interval.tv_usec = 250000*3;
  
	/* Start a virtual timer*/
	setitimer(ITIMER_VIRTUAL,&timer,NULL);
	while(1);
}
