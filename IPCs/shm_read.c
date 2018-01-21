#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h> 
#include <stdio.h>  
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 


int main (void)
{
	int fd;
	char buf[20];

  	if((fd = shm_open("/mydata.shared", O_RDONLY, 0644)) == -1) {
		perror("shm_open");
		return 1;
	}

	read(fd, buf, 18);
	buf[18] = '\0';
	printf("Read data: %s\n", buf);

	close(fd);
	
	return 0;
}
