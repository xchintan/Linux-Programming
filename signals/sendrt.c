#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int main(int argc, char **argv)
{
    pid_t pid;
    int i;

    /*union sigval value;

    value.sival_int = 100; 
    */

    pid = atoi(argv[1]);
    printf("Sending signal %d\n", 35);

    for (i=47; i<67; i++) {
        if (sigqueue(pid, 35, (union sigval) i) == -1) {
            printf("failed to deliver %d\n", i);
            perror("error: ");
        } else {
            printf("Signal delivered with data: %d\n", i);
        }

        /* sleep(1); */
    }

    return 0;
}


