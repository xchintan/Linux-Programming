#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int john_balance = 5000;
int smith_balance = 2000;
int joe_balance = 2000;

pthread_mutex_t mutex;

void transfer_fund1() 
{
	if ((john_balance - 3000) <= 0) {
		printf("Insufficient funds...\n");
		return;
	}
	sleep(1);
	john_balance -= 3000;
	sleep(1);
	smith_balance += 3000;
}

void transfer_fund2() 
{
	if ((john_balance - 3000) <= 0) {
		printf("Insufficient funds...\n");
		return;
	}
	sleep(1);
	john_balance -= 3000;
	sleep(1);
	joe_balance += 3000;
}

void *thread_function(void *arg) {
   pthread_mutex_lock(&mutex);
   if (strcmp((char *) arg, "thread1") == 0) {
	   transfer_fund1();
   } else if (strcmp((char *)arg, "thread2") == 0) {
	   transfer_fund2();
   }
   pthread_mutex_unlock(&mutex);

   return NULL;
}

int main(void) {

  pthread_t thread1, thread2;

  pthread_mutex_init(&mutex, NULL);

  printf("John's balance: %d\nSmith's balance: %d\nJoe's balance: %d\n",
		 john_balance, smith_balance, joe_balance);
  printf("------------------------\n");
   

  if (pthread_create(&thread1, NULL, thread_function, "thread1")) {
    printf("error creating thread.");
    return 1;
  }

  if (pthread_create(&thread2, NULL, thread_function, "thread2")) {
    printf("error creating thread.");
    return 1;
  }


  if (pthread_join(thread1, NULL ) ) {
    printf("error joining thread.");
    return 1;
  }

  if (pthread_join(thread2, NULL ) ) {
    printf("error joining thread.");
    return 1;
  }
  pthread_mutex_destroy(&mutex);
  printf("John's balance: %d\nSmith's balance: %d\nJoe's balance: %d\n",
		 john_balance, smith_balance, joe_balance);
  printf("------------------------\n");

  return 0;
}
