#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int main()
{
    int i;

    printf("Waiting for 10 seconds...\n");
	/*  alarm(): 
			arranges for a SIGALRM signal to be delivered to the 
			calling process in seconds seconds.    
	*/
    alarm(5);
    
    for (i=0; i<100; i++) {
        printf("Counting %d\n", i);
        sleep(1);
    }

    printf("Alarm complete...\n");

    return 0;
}

