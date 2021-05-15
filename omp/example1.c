#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int who_am_i (int id) {
  return id;
}

int main(int argc, char *argv[]) {
  int nthreads, tid, var1;

  /* Divide em um conjunto de threads, cada uma com suas próprias variáveis */
  // default(shared) garante que todas as variáveis que não estejam explicitamente definidas como privadas
  // (private) serão compartilhadas e garantidas por um processo de exclusão mútua
  #pragma omp parallel shared(var1) private(nthreads, tid)
  {
    /* Obtém o id da thread */
    tid = omp_get_thread_num(); //cada thread obtém o seu próprio id
    printf("Hello World from thread = %d\n", tid);
    // system("stress -c 1");

    /* Restrição de execução para uma thread específica */
    if (tid == 0) {
      nthreads = omp_get_num_threads(); //obtém-se o total de threads
      printf("I'm thread %d and the total number of threads is = %d\n", tid, nthreads);
    }

  } /* Todas as threads se juntam ao processo principal e encerram */
    // continuar com processamento sequencial
  printf("Processamento sequencial...\n\n");

  #pragma omp parallel private(nthreads, tid, var1)
  {
    tid = omp_get_thread_num();
    printf("Novo bloco paralelo executado pela thread %d\n", tid);
    // ..... novo bloco paralelo
  }
}