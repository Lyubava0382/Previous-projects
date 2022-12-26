#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#define MAX_LENGTH 1000

int main(int argc, char* argv[])
{
	srand(time(0));
	double time_start, time;
	int size, rank, n, a, newrank, new_a;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int* array = new int[size];
	for (int i = 0; i < size; i++) array[i] = 0;
	MPI_Comm newcomm;
	a = rank + 1;
	time_start = MPI_Wtime();
	if (rank == 0) {
		n = 1;
	}
	else if (rank == 1) n = 2;
	else n = rand() % 2 + 1;

	MPI_Comm_split(MPI_COMM_WORLD, n, rank, &newcomm);
	printf("rank = %d, N = %d, A = %d\n", rank, n, a); 
	printf("Received counts:\n");
	int root = 0;
	MPI_Allgather(&a, 1, MPI_INT, *&array, 1, MPI_INT, newcomm);
	for (int i = 0; array[i] > 0; i++) {
		printf("a[%d] = %d\n", i, array[i]);
	}

	MPI_Finalize();
	return 0;
}
