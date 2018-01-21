#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define BUFFER_64K 1024*64

/* 
	go to /proc/pid/
	check various files and attributes
	Most importantly,check /proc/pid/maps 
		a) Prior to malloc begins
		b) See where malloc address belongs
		c) Increase the buffer size beyon 120K see in which region you get address

	Use strace to see which system call is invoked to allocate the  page
		a) brk #for allocations less than 120K
		b) mmap 
*/
int main() {
	char *ptr[20];
	int i=0;
	printf("pid: %d\n",getpid());
	printf("Ready to start allocation\n");
	getchar();

	for(i=0; i< 20;i++) {
		ptr[i] = malloc(BUFFER_64K);
		printf("Allocation No: %d : %p\n",i+1,ptr[i]);
		getchar();
	}
	for(i=0; i< 20;i++) {
		free(ptr[i]);
		printf("Freed ...%d \n",i+1);
		getchar();
	}
	return 0;
}
