#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h> 


void critical_function(char *id,sem_t *sem) 
{
	int i;
	for(i=1;i<10;i++) {
		sem_wait(sem);
		printf("[%s]:\t%d\n",id,i);
		sem_post(sem);
		sleep(3);
	}
	return;
}

int main()
{
	sem_t *sem; 
	pid_t pid;
	sem = sem_open("/mysem", O_RDWR | O_CREAT ,0666,1);
	sem_init(sem,1,1); // check for return
	
	pid = fork();

	if(0==pid) {
		critical_function("child",sem);
	} else {
		critical_function("parent",sem);
	} 

	sem_close(sem);
	return 0;							
}


