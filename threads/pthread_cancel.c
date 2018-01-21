#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void *thread_function(void *arg) {
  static int i;
  for (i=0;; i++) {
    printf("In %s, count = %d\n", (char *)arg, i);
  /*  sleep(1); */
  }

  return NULL;
}

int main(void) {

  pthread_t mythread;
  int i;

  if (pthread_create(&mythread, NULL, thread_function, "thread1")) {
    fprintf(stderr, "error creating thread.");
    return 1;
  }
 
 /* thread_function("main thread"); 
 */
  for (i=0; i<5; i++) {
    printf("In main: count = %d\n", i);
    sleep(1);
  }
  printf("Main: waiting for threadfunction to complete...\n");
  pthread_cancel(mythread);
  printf("Main: sent cancellation request...\n");


  if (pthread_join(mythread, NULL)) {
    fprintf(stderr, "error joining thread.");
    return 1;
  }

  printf("Main: threadfunction complete.\n");

  return 0;
}
