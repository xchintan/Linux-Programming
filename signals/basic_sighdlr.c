#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signum)
{
    printf("Received signal %d\n", signum);
    sleep(10); 
    printf("Signal handler for %d finished.\n", signum);
}


int main()
{
    printf("Pid = %d\n", getpid());

    signal(SIGHUP, sig_handler); 
    signal(SIGQUIT, sig_handler); 
    signal(SIGINT, sig_handler); 
    signal(SIGUSR1, sig_handler); 
    signal(SIGUSR2, sig_handler); 

    while (1) {
    	sleep(3); /* This is your chance to press CTRL-C */
        printf("Counting...\n");
    }

    return 0;
}
