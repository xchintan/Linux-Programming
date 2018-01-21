#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/mman.h>
//#include <string.h>

sem_t *sem_factory(int type);	//Defined after main
void sem_free(sem_t *sem);		//Defined after main

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
	sem_t *sem = sem_factory(0); 
	pid_t pid;
	/*  sem_init(sem_t *sem, int pshared, int value)
		The pshared argument indicates whether this semaphore is to be shared 
		between the	threads  of  a  process,  or between processes.

		1) If  pshared  has  the  value  0,  then  the semaphore is shared 
		between the threads. It should be accessible to all threads, so 
		it should be either global or located on heap.

		2) If  pshared  is  nonzero,  then the semaphore is shared between 
		processes, and should be located in a region of shared memory / mmap region.

		value: Initial value of semaphore
	*/
	sem_init(sem,1,1); // check for return
	
	pid = fork();

	if(0==pid) {
		critical_function("child",sem);
	} else {
		critical_function("parent",sem);
	} 

	sem_free(sem);
	return 0;							
}


sem_t *sem_factory(int type)
{
	//Type0:  Anonymous.	Type1:	Named
	sem_t *sem = NULL;

	sem = (sem_t*) mmap(NULL,sizeof(sem_t), PROT_READ | PROT_WRITE,
						MAP_ANONYMOUS | MAP_SHARED,
						-1, 0);
	if(MAP_FAILED == sem) {
			sem = NULL;
	}
	return sem;
}

void sem_free(sem_t *sem) {
	if(sem) {
		munmap(sem,sizeof(sem_t));
	}
	return;
}
