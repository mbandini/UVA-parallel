// Neste exemplo, o processo de rank zero irá enviar o valor 1000 para os demais processos. Os demais processos, por sua vez,
// enviarão de volta o próprio rank para o processo zero

#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
	int size, rank, length, i, value;
	char hostname[50];
	MPI_Status Status;

	MPI_Init (&argc, &argv);

	MPI_Comm_size (MPI_COMM_WORLD, &size);

	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

	MPI_Get_processor_name (hostname, &length);

	if (rank == 0) {
		value = 1000;
		// MPI_Brodcast(); // envia para todos os processos
		for (i = 1; i < size; i++) {
			// PARAMS: dado_enviado, qtde_dados, tipo_dado, proc_destino, tag_msg, comunicador
			MPI_Send(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf ("Processo 0 enviando %d para o processo %d\n", value, i);
		}
	}
	else {
		// PARAMS: dado_recebido, qtde_dados, tipo_dado, proc_origem, tag_msg, comunicador, status
		MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status);
		printf ("Processo %d executou em %s e recebeu valor %d de 0\n", rank, hostname, value);
	}

	// printf ("Quantidade de processos = %d | Meu rank = %d | Maquina = %s\n", size, rank, hostname);

	MPI_Finalize ();

	return 0;
}
