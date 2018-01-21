#include <semaphore.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
sem_t sem_odd;
sem_t sem_even;

void* print_odd_thread(void *arg) {
	int i=1;
	for(i=1;i<30;i=i+2) {
		sleep(2);
		sem_wait(&sem_odd);
		printf("thread[odd]:	%d\n",i);
		sem_post(&sem_even);
	}
	return;

} 
void* print_even_thread(void *arg) {
	int i=2;
	for(i=2;i<30;i=i+2) {
		sleep(1);
		sem_wait(&sem_even);
		printf("thread[even]:	%d\n",i);
		sem_post(&sem_odd);
	}
	return;

}
int main()
{
	pthread_t t_odd,t_even;
	int ret;
	//Thread syncronization
	//Since it is a thread, we don't need mmap, so either we
	// can allocate semaphore on heap or use the global semaphore
	sem_init(&sem_odd,1,1);
	sem_init(&sem_even,1,0); //Lock even - it will get unlocked by odd thread


	ret = pthread_create(&t_odd,NULL,print_odd_thread,NULL);
	ret = pthread_create(&t_even,NULL,print_even_thread,NULL);
	
	pthread_join(t_odd,NULL);
	pthread_join(t_even,NULL);
	
	return 0;
}

