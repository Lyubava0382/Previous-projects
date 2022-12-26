#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#define MAX_LENGTH 1

int main(int argc, char* argv[])
{
	int size, rank;
	MPI_Status status;
	int* message = (int*)(calloc(MAX_LENGTH, sizeof(int)));
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Request req;
	if ( rank == 0 && rank < size - 1) {
		for (int i = 1; i < size; i++) {
			MPI_Isend(message, MAX_LENGTH, MPI_INT, i,
				0, MPI_COMM_WORLD, &req);
			printf("\nprocess %d, received message length %d from process %d, time %f", rank, MAX_LENGTH, i, MPI_Wtime());

			MPI_Recv(message, MAX_LENGTH, MPI_INT, i, 0, MPI_COMM_WORLD,
				&status);
			printf("\nprocess %d, received message length %d from process %d, time %f", rank, MAX_LENGTH, i, MPI_Wtime());

		}
	}
	else if (rank > 0) {
		MPI_Recv(message, MAX_LENGTH, MPI_INT, 0, 0, MPI_COMM_WORLD,
			&status);
		printf("\nprocess %d, received message length %d from process %d, time %f", rank, MAX_LENGTH, 0, MPI_Wtime());
		MPI_Isend(message, MAX_LENGTH, MPI_INT, 0,
			0, MPI_COMM_WORLD, &req);
		printf("\nprocess %d, send message length %d to process %d, time %f", rank, MAX_LENGTH, 0, MPI_Wtime());

	}

	MPI_Finalize();
	return 0;
}
