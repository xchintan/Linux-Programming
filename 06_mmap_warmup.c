#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>


int main() 
{
	int fd;
	char *buf = NULL;
	
	fd = open("a.txt", O_RDWR | O_CREAT | O_TRUNC,0644);
	ftruncate(fd,256);
	
	printf("pid = %d\n",getpid());
	
	buf = mmap(NULL,256,PROT_WRITE, MAP_SHARED,fd,0L);
	if(buf == MAP_FAILED) {
		printf("Map failed\n");
		exit(0);
	}
	getchar();

	memcpy(buf,"Hello World",strlen("Hello World"));
	munmap(buf,256);	
	close(fd);
	return 0;

}

