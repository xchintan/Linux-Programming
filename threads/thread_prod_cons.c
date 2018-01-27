#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/*Producer and Consumer*/

void* producer_thread(void *arg) {
	int write_fd = *(int*)arg;
	int msg = 13;
	while(1) {
		write(write_fd,(char*)&msg,4);
		msg += 2;
		sleep(2);
	}

	return;
}

void* consumer_thread(void *arg) {
	int read_fd = *(int*)arg;
	int msg = 0;
	while(1) {
		read(read_fd,(char*)&msg,4);
		printf("\t[Thread] Msg Rcvd = %d\n", msg);
	}
	return;
}
int main()
{
	int pipe_fds[2];
	int read_fd,write_fd;
	int ret=0;
	pthread_t prod, cons;

	ret = pipe(pipe_fds);
	if(ret == -1) {
		printf("Pipe() failed\n");
		return -1;
	}
	read_fd = pipe_fds[0];
	write_fd = pipe_fds[1];

	//Spawn a producer thread
	ret = pthread_create(&prod,NULL,producer_thread,(void*) (&write_fd));
	ret = pthread_create(&cons,NULL,consumer_thread,(void*) (&read_fd));

	sleep(10);
	printf("Terminating threads and exiting ...\n");
	pthread_cancel(prod);
	pthread_cancel(cons);
	return 0;
}
