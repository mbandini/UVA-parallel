/*
Criar duas threads que processam o mesmo vetor definido na função principal
- A thread 0 irá somar os elementos do vetor
- A thread 1 irá encontrar o maior valor presente no vetor
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 2
#define SIZE 10

void *sum_vector(void *vector)
{
  int *v = (int *) vector;
  int i, sum = 0;

  for (i = 0; i < SIZE; i++) {
	  sum += v[i];
  }

  printf("Somatorio = %d\n", sum);

  pthread_exit(NULL);
}

void *max_elem(void *vector) {
  int *v = (int *) vector;
  int i, max = v[0];

  for (i = 1; i < SIZE; i++) {
    if (v[i] > max) {
      max = v[i];
    }
  }

  printf("Maior elemento do vetor = %d\n", max);

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int v[SIZE] = {2, 7, 9, 11, 5, 1, 0, 8, 15, 4};
  int rc;
  long t;

  for (t = 0; t < NUM_THREADS; t++) {
    if (t == 0) {
      rc = pthread_create(&threads[t], NULL, sum_vector, (void *) &v);
      if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
      }
    }
    else {
      rc = pthread_create(&threads[t], NULL, max_elem, (void *) &v);
      if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
      }
    }
  }

  pthread_exit(NULL);

  return 0;
}