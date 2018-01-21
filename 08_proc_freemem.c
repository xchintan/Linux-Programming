/* 
    Prints free memory. This program reads /proc/meminfo and 
	prints MemFree.
*/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>


#define BUFFERSIZE 4096
#define MEM_FILE "/proc/meminfo"

int main(int argc, char *argv[])
{
    int fd;
    char buf[BUFFERSIZE]="";
    char tok1[10], tok2[10], tok3[10], tok4[10];
    int freemem;

    fd = open(MEM_FILE, O_RDONLY);
	read(fd, buf, BUFFERSIZE);

    sscanf(buf, "%s %s %s %s %d", tok1, tok2, tok3, tok4, &freemem); 
    printf("Free memory: %d kilobytes\n", freemem);
    close(fd);
    return 0;

}
    
    
