#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

struct thread_data {
	long thread_id;
	long sum;
};

void *PrintHello(void *threadarg) {
  struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
  long taskid = my_data->thread_id;
	long sum = my_data->sum;
	printf("Hello World! It's me, thread #%ld, with sum = %ld!\n", taskid, sum);
	pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
  struct thread_data thread_data_array[NUM_THREADS];
	int rc;
	long t;
	for(t = 0; t < NUM_THREADS; t++){
   	thread_data_array[t].thread_id = t;
   	thread_data_array[t].sum = t + 2;
   	rc = pthread_create (&threads[t], NULL, PrintHello, (void *) &thread_data_array[t]);
		if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
	pthread_exit(NULL);
}