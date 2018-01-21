#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    printf("HZ = %ld\n", sysconf(_SC_CLK_TCK));
    return 0;

}    


