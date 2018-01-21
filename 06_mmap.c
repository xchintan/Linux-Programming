#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#define error(x, y) fprintf(stderr, "%s: error while %s on %s: %s\n", argv[0], x, y, strerror(errno))

int main(int argc, char *argv[]) 
{
    int ret = EXIT_FAILURE;

    char *buf;

    printf("Pid = %d\n", getpid());
    getchar();

    buf = mmap(NULL, 8192*1024, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0L);
    printf("Allocated buf at %p\n", buf);
    getchar();

    munmap(buf, 8192*1024);
    getchar();

    ret = EXIT_SUCCESS;

exit_program:
    return ret;
}    


