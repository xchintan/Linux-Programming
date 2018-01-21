#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>

#define MAX_THREAD 3

/* __thread is for thread local storage (TLS)   
	A mechanism by which variables are allocated such that there is one instance 
	of the variable per thread.
	Can be used with global and static specifiers
*/

__thread int variable = 0;

void *thread_function(void *arg) {
	int id =  *(int*)arg;
	int count = id*100;
  	while (1) {
     	printf("Thread %d [%d][%d]: counting: %d\n", 
				id, getpid(), syscall(SYS_gettid), count++);
     	sleep(1); 
  	}     
}

int main(void) {

	pthread_t pthrd[MAX_THREAD];
	int i, ret;
	int th_arg[MAX_THREAD];

	printf("This Program will spawn N threads, each will print pid/tid and count\n");
	printf("Press Any key to start and stop\n");
	getchar();

	for (i=0; i<MAX_THREAD; i++) {
		th_arg[i] = i+1;
     	ret = pthread_create(&pthrd[i], NULL, 
							thread_function, 
							(void*)&th_arg[i]);
		if(ret) {
		  fprintf(stderr, "failed to create thread %d: %s\n",
				  i, strerror(ret));
		  abort();
		}
	}
	getchar();
  	return 0;
}
