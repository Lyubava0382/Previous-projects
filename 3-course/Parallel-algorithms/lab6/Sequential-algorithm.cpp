#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#define MAX_LENGTH 1000
#define SIZE 6

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	srand(time(0));
	printf("Size of matrix: %d\n", SIZE);
	int first_matrix[SIZE][SIZE];
	int second_matrix[SIZE][SIZE];
	int result[SIZE][SIZE];;

	printf("\nFirst matrix\n\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			first_matrix[i][j] = rand() % 150;
			printf("\t%d", first_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\nSecond matrix\n\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			second_matrix[i][j] = rand() % 150;
			printf("\t%d", second_matrix[i][j]);
			result[i][j] = 0;
		}
		printf("\n");
	}
	double time = MPI_Wtime();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			for (int k = 0; k < SIZE; k++) {
				result[i][j] += second_matrix[k][j] * first_matrix[i][k];
			}
		}
	}
	printf("\nResults\n\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("\t%d", result[i][j]);
		}
		printf("\n");
	}
	printf("\nTime:\t%f", MPI_Wtime() - time);
	MPI_Finalize();
	return 0;
}

