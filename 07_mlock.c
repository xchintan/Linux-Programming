#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

    printf("Pid = %u\n", getpid());
    getchar();

    mlockall(MCL_CURRENT | MCL_FUTURE); 
    getchar();

    munlockall(); 
    getchar();

    return 0;
}
