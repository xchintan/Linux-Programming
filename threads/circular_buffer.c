#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define BUF_SIZE	8
//Global data - needs to be locked
int buffer[BUF_SIZE] = {0};
int head =0; 
int tail =0;
int size;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*Producer and Consumer*/

void* producer_thread(void *arg) {
	int msg = 13;
	int next  = 0;
	while(1) {
		sleep(1);
		pthread_mutex_lock(&mutex);
		next = (head + 1) % BUF_SIZE; //This is most important step
		if(next == tail) { 
			printf("Buffer is full \n");
		} else {
			buffer[head] = msg;
			head = next;
			msg += 2;
		}
		pthread_mutex_unlock(&mutex);
	}
	return;
}

void* consumer_thread(void *arg) {
	int msg = 0;
	while(1) {
		sleep(2);
		pthread_mutex_lock(&mutex);
		if(head==tail) {
			printf("Buffer is empty\n");
		} else {
			msg = buffer[tail];
			printf("\tRcvd Msg[%d] = %d\n",tail, msg);
			tail = (tail+1) % BUF_SIZE;
		}
		pthread_mutex_unlock(&mutex);
	}
	return;
}
int main()
{
	int ret=0;
	pthread_t prod, cons;

	//Spawn a producer thread
	ret = pthread_create(&prod,NULL,producer_thread,NULL);
	ret = pthread_create(&cons,NULL,consumer_thread,NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
	return 0;
}
