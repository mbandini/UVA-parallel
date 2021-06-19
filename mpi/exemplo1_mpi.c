#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
	int size, rank, length;
	char hostname[50];

	// Inicializando ambiente MPI
	MPI_Init (&argc, &argv);

	// obter quantidade de processos paralelos
	// MPI_COMM_WORLD = comunicador padrão criando pelo MPI_Init
	MPI_Comm_size (MPI_COMM_WORLD, &size);

	// cada processo obtém o seu rank
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf ("Autor: Matheus Bandini\n");
    printf ("Matricula: 88888888\n");
	  printf ("Data: 05/06/2020\n");
		printf ("======================\n");
	}

	// obtém o nome da máquina na qual o processo está executando
	MPI_Get_processor_name (hostname, &length);

	printf ("Quantidade de processos = %d | Meu rank = %d | Maquina = %s\n", size, rank, hostname);

	// Finalizando o ambiente MPI
	MPI_Finalize ();

	return 0;
}
