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
    size_t total, nwritten;
	off_t offset =0;
    struct stat info;

    if (argc < 3) {
        fprintf(stderr, "usage: %s source destination.\n", argv[0]);
        exit(0);
    }

    src_fd = open(argv[1], O_RDONLY);
    fstat(src_fd, &info);
	
	dst_fd = open(argv[2], O_RDWR | O_CREAT, 0644);
	
	total = info.st_size;
	do {
		nwritten = sendfile(dst_fd,src_fd,offset,total);
		total -= nwritten;
	}while(total);
	
    ret = EXIT_SUCCESS;
	printf("copy done... \n");
	getchar();
    close(dst_fd);
    close(src_fd);
    return ret;
}
