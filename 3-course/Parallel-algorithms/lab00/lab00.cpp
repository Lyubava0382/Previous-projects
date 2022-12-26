#include <stdio.h>
#include "mpi.h"
int main(int argc, char* argv[]) {
	int rank, n, i, message;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		printf("\n Hello from process %3d", rank);
		for (i = 1; i < n; i++) {
			MPI_Recv(&message, 1, MPI_INT, i,
				MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("\n Hello from process %3d", message);
		}

	}
	else MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}
