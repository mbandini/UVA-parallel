#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 6

// GLOBAL VARS
int graph[NUM_THREADS][NUM_THREADS] = {{0, 1, 0, 0, 2, 0}, {1, 0, 3, 0, 2, 0}, {0, 3, 0, 6, 0, 0}, {0, 0, 6, 0, 4, 3}, {2, 2, 0, 4, 0, 0}, {0, 0, 0, 3, 0, 0}};
int degrees[NUM_THREADS];
long maxDegree = 0;
pthread_mutex_t mutexcomp;

void *degree(void *threadid) {
  long tid, i, edges = 0;
  tid = (long)threadid;
  for (i = 0; i < NUM_THREADS; i++) {
    if (graph[tid][i] != 0) {
      edges++;
    }
  }

  pthread_mutex_lock(&mutexcomp);
  if (edges > maxDegree) {
    maxDegree = edges;
  }
  pthread_mutex_unlock(&mutexcomp);

  degrees[tid] = edges;
  pthread_exit((void*) tid);
}

void *election(void *threadid) {
  long tid;
  tid = (long)threadid;
  if (degrees[tid] == maxDegree) {
    printf("Vertex %c has the maximum degree in graph: %ld\n", (char) tid + 65, maxDegree);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  void *status;
  int rc;
  long t, i;

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  for (t = 0; t < NUM_THREADS; t++) {
    rc = pthread_create(&threads[t], &attr, degree, (void *)t);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  pthread_attr_destroy (&attr);

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], &status);
  }

  printf("Max degree: %ld edges\n", maxDegree);
  for (i = 0; i < NUM_THREADS; i++) {
    printf("Degree of vertex %c: %d edges\n", (char) i + 65, degrees[i]);
  }

  printf("+++++++++++++++++++ FINAL RESULTS +++++++++++++++++++\n");
  for (t = 0; t < NUM_THREADS; t++) {
    rc = pthread_create(&threads[t], NULL, election, (void *)t);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  pthread_exit(NULL);
}