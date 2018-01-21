#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    int fd;
    char buf[] = "hello";

    fd = open("a.txt", O_WRONLY | O_CREAT, 0644);

    lseek(fd, 1024, SEEK_END); 

    write(fd, buf, strlen(buf));
    close(fd);


    return 0;
 
}

