/*
Criar duas threads que processam o mesmo vetor definido na função principal
- A thread 0 irá somar os elementos do vetor
- A thread 1 irá encontrar o maior valor presente no vetor
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5
#define SIZE 10

void *SumVector(void *vector)
{
  int *v = (int *) vector;
    int i, sum = 0;

    for (i = 0; i < SIZE; i++) {
	    sum += sum + v[i];
    }

    printf("Somatorio = %d\n", sum);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("In main: creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
    if (rc)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  /* Last thing that main() should do */
  pthread_exit(NULL);

  return 0;
}