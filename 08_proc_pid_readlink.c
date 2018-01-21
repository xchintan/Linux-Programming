#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char buf[32]="";
    readlink("/proc/self", buf, 31);
    printf("Pid = %s\n", buf);
    return 0;
}


