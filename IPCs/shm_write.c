#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h> 
#include <stdio.h>  
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <fcntl.h>


int main (void)
{
	int fd;
	char buf[] = "This is test data";

  	if((fd = shm_open("/mydata.shared", O_CREAT | O_WRONLY, 0644)) == -1) {
		perror("shm_open");
		return 1;
	}

  /*  ftruncate(fd, strlen(buf)); */
	write(fd, buf, strlen(buf));
	close(fd);

	return 0;
}
