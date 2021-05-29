/*
  OMP_NUM_THREADS  = Especifica o padrão da quantidade de threads executadas
  OMP_THREAD_LIMIT = Especificar a quantidade máxima possível de threads que podem ser criadas
  Hierarquia:
  OMP_THREAD_LIMIT -> especificado em código -> OMP_NUM_THREADS -> qtd de núcleos da máquina
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  GOMP_CPU_AFFINITY = Permite especificar qual thread executará em qual núcleo
  Exemplo:
  GOMP_CPU_AFFINITY="0 2 4 6"
                     ^ ^ ^ ^
                     | | | |
  Threads ---------- 0 1 2 3
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define QTD 8

void who_am_i (int id) {
	if (id == 0) {
		printf ("I'm the main!!!!\n");
	}
	else {
		printf ("I am process %d\n", id);
	}
}

void show_elem (int *v, int id) {
	printf ("I am thread %d and my value in the array is %d\n", id, v[id]);
}


int main (int argc, char *argv[]) {
	int nthreads, tid, value = 0, vet[QTD] = {3, 2, 7, 1, 0, 9, 4, 5};

	#pragma omp parallel shared (value, vet) private (nthreads, tid) num_threads (QTD)
	{
		tid = omp_get_thread_num ();
		// printf ("Hello from thread %d\n", tid);
		// who_am_i (tid);
		// show_elem (vet, tid);
		if (tid != 0) {
			value = tid; // troca do valor da variável compartilhada
			printf ("Process %d changed value to %d\n", tid, value);
		}

		if (tid == 0 ) {
			nthreads = omp_get_num_threads ();
			printf ("I am thread %d and we have %d threads\n", tid, nthreads);
			value = 10; // troca do valor da variável compartilhada
			printf ("Process %d changed value to %d\n", tid, value);
		}
    // system("stress -c 1");
	}

	return 0;
}








