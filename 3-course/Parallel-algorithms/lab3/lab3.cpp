#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#define MAX_LENGTH 1000

int main(int argc, char* argv[])
{
	srand(time(0));
	double time_start, time;
	int size, rank, count = 0, index = 0, index_res = 0;
	double double_x;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int  rbuf[3];
	int  root = rank;
	int* array = new int[size * 3];
	time_start = MPI_Wtime();
	if (rank == 0) {
		for (int i = 0; i < size * 3; i++) {
			array[i] = rand() % 100;
		}
	}

	int* numbers = (int*)malloc(sizeof(int) * 3);

	MPI_Scatter(array, 3, MPI_INT, numbers,
		3, MPI_INT, 0, MPI_COMM_WORLD);
	printf("\nprocess %d:\n", rank);
	for (int c = 0; c < 3; c++)
		printf("numbers[%d] = %d\n", c, numbers[c]);
	MPI_Finalize();
	return 0;
}
