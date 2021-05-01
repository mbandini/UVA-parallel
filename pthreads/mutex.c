#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 6

pthread_t threads[NUM_THREADS];
pthread_mutex_t mutexcomp; // mutex que irá controlar o acesso a variável varComp
long varComp; // variável a ser compartilhada

void *varMutex(void *t) {
	long tid = (long) t;

	pthread_mutex_lock (&mutexcomp); // inicio da seção crítica
	printf ("######\tThread %ld iniciando MUTEX e modificando variavel compartilhada\t######\n", tid);
	varComp = 1;
	varComp = tid * varComp;
	printf ("\t#\tThread %ld computou o valor %ld para varComp\t\t#\n", tid, varComp);
	printf ("######\tThread %ld finalizando MUTEX e modificando variavel compartilhada\t######\n", tid);
	pthread_mutex_unlock (&mutexcomp); // fim da seção crítica

	pthread_exit (NULL);
}

int main (int argc, char *argv[]) {

	int rc;
	long t;

	pthread_mutex_init (&mutexcomp, NULL);

	for(t = 0; t < NUM_THREADS; t++) {
	  pthread_mutex_lock (&mutexcomp); // início da sessão crítica imposta pela main
		printf ("######\tPrincipal iniciando MUTEX e modificando variavel compartilhada\t######\n");
    varComp = 1;
    varComp = -1*varComp;

    printf ("\t#\tPrincipal computou o valor %ld para varComp\t\t#\n", varComp);
    printf ("######\tPrincipal finalizou MUTEX e modificou variavel compartilhada\t######\n");
    pthread_mutex_unlock (&mutexcomp); // fim da sessão crítica imposta pela main

		rc = pthread_create (&threads[t], NULL, varMutex, (void *) t);
		if (rc) {
			printf ("ERROR; return code from pthread_create() is %d\n", rc);
			exit (-1);
		}
	}

	pthread_mutex_destroy (&mutexcomp);

	pthread_exit (NULL);

  return 0;
}