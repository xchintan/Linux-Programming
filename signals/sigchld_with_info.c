#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/ucontext.h>

struct sigaction act;

void sighandler(int signum, siginfo_t *info, void *ptr)
{
    printf("Received signal %d\n", signum);
    printf("Signal originates from process %d\n", info->si_pid);
}

int main()
{
    printf("I am %lu\n", (unsigned long)getpid());

    act.sa_sigaction = sighandler;
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &act, NULL);

    while (1) {
	   sleep(1);
	   printf("Counting...\n");
    }

    return 0;
}
