#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>



int main(int argc, char *argv[])
{
    int ret = EXIT_FAILURE;
    int src_fd, dst_fd;
    ssize_t nread, nwrite;
    struct stat info;
	char *rbuf = NULL, *wbuf=NULL;

    if (argc < 3) {
        fprintf(stderr, "usage: %s source destination.\n", argv[0]);
        exit(0);
    }

    src_fd = open(argv[1], O_RDONLY);
    fstat(src_fd, &info);
    rbuf = (char *)mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE,
                       src_fd, 0L);
    if (rbuf == MAP_FAILED) {
        exit(-1);
    }
	
	//For memcpy() O_RDWR is needed, O_WRONLY results in crash
	dst_fd = open(argv[2], O_RDWR | O_CREAT, 0644);
	ftruncate(dst_fd, info.st_size);
	wbuf = (char*) mmap(NULL,info.st_size,PROT_WRITE, MAP_SHARED,
						dst_fd,0L);

	memcpy(wbuf,rbuf,info.st_size);

    ret = EXIT_SUCCESS;
	printf("copy done... \n");
	getchar();
    munmap(rbuf, info.st_size);
    munmap(wbuf, info.st_size);
    close(dst_fd);
    close(src_fd);
    return ret;
}
