#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    int fd;

    fd = open("abc.tx", O_WRONLY | O_CREAT, 0644);

    ftruncate(fd, 1024*2);

    close(fd);

    return 0;

}

