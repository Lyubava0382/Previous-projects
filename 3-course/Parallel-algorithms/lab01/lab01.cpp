#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#define MAX_LENGTH 1

int main(int argc, char* argv[])
{
	int size, rank;
	double time_start, time;
	MPI_Status status;
	int* message_1 = (int*)(calloc(MAX_LENGTH, sizeof(int)));
	int* message_2 = (int*)(calloc(MAX_LENGTH + 10, sizeof(int)));
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	time_start = MPI_Wtime();
	if ((rank % 2) == 0 && rank >= 0) {
		if (rank < size - 1)
			MPI_Send(message_1, MAX_LENGTH, MPI_INT, rank + 1, 0,
				MPI_COMM_WORLD);
	}
	else if (rank >= 0)
		MPI_Recv(message_2, MAX_LENGTH, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
			&status);

	time = MPI_Wtime() - time_start;
	printf("\nprocess %d, message length = %d, time = %f", rank, MAX_LENGTH, time);
	MPI_Finalize();
	return 0;
}
