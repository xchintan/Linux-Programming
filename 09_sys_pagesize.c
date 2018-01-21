#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("Page size: %u\n", sysconf(_SC_PAGESIZE));

    return 0;
}

