#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int myglobal;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg) {
   int i;
   for (i=0; i<100; i++) {
        pthread_mutex_lock(&mutex);
        myglobal++;
	    printf("Counting[%s] %d\n", (char *)arg, i);
        pthread_mutex_unlock(&mutex);
   }
   return NULL;
}

/*
<rant>
	Mutex is for protecting critical data, not for synronization.
	This program spwans two threads and each thread (N times):
		acuquires the lock,increments the global variable 
	Mutex ensures searialized access.

	It may so  happen, that one of the thread lock everytime, making
	other process to wait longer. So again, a bad design.

	This pgrm is to learn syntax of mutex.
	
</rant>
*/
int main(void) {

	pthread_t t1,t2;
  
	pthread_create(&t1, NULL, thread_function, "Thread1");
	pthread_create(&t2, NULL, thread_function, "Thread2");

  /*This is dirty - waiting for each thread to join*/
  if ( pthread_join ( t1, NULL ) ) {
    printf("error joining thread1.");
    abort();
  }

 if ( pthread_join ( t2, NULL ) ) {
    printf("error joining thread2.");
    abort();
  }
  printf("\nmyglobal equals %d\n",myglobal);

  exit(0);

}
