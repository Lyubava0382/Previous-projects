#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#define MAX_LENGTH 1000
#define SIZE 4

void matrixprint(int** matr, int size) {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			printf("\t%d", matr[x][y]);
		}
		printf("\n");
	}
}

void lineOf(int** matrix, int h, int w, int* line) {
	int count = 0;
	for (int x = 0; x < h; x++) {
		for (int y = 0; y < w; y++) {
			line[count++] = matrix[x][y];
		}
	}
}

void lineTo(int** matrix, int size, int* line) {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			matrix[x][y] = line[x * size + y];
		}
	}
}


int main(int argc, char* argv[]) {
	int number, rank, source, rank_dest;
	MPI_Status status;
	MPI_Comm new_comm;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &number);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	srand(time(0));
	double time = MPI_Wtime();
	int** first_matrix, ** second_matrix, ** result{}, * first_line{}, * second_line{}, 
		* result_line{}, * first_buffer, * second_buffer, * tmp, paragraph, length;
	if (rank == 0) {
		printf("Size of matrix %d\n", SIZE);
		paragraph = (number - SIZE % number) % number;
		first_matrix = (int**)calloc(paragraph + SIZE, sizeof(int*));
		second_matrix = (int**)calloc(paragraph + SIZE, sizeof(int*));
		result = (int**)calloc(SIZE, sizeof(int*));
		int new_size = paragraph + SIZE;
		first_line = new int[new_size];
		second_line = new int[new_size];
		result_line = new int[new_size * SIZE]; 
		for (int i = 0; i < new_size; i++) {
			first_matrix[i] = new int[SIZE];
			second_matrix[i] = new int[SIZE];
			result[i] = new int[SIZE];
		}
		length = round(new_size / number);
		for (int x = 0; x < SIZE; x++) 
			for (int y = 0; y < SIZE; y++) {
				first_matrix[x][y] = rand() % 150;
				second_matrix[x][y] = rand() % 150;
				result[x][y] = 0;
			}
		printf("\n\nFirst matrix\n");
		matrixprint(first_matrix, SIZE);
		printf("\n\nSecond matrix\n");
		matrixprint(second_matrix, SIZE);
		lineOf(first_matrix, new_size, SIZE, first_line);
		lineOf(second_matrix, new_size, SIZE, second_line);
	}
	first_buffer = new int[length * SIZE];
	second_buffer = new int[length * SIZE];
	tmp = new int[length * SIZE];
	int dims[1] = { number };
	int periods[] = { 1, 0 };
	MPI_Cart_create(MPI_COMM_WORLD, 1, dims, periods, 1, &new_comm);
	MPI_Comm_rank(new_comm, &rank);
	int int_size = SIZE;
	MPI_Bcast(&int_size, 1, MPI_INT, 0, new_comm);
	MPI_Bcast(&length, 1, MPI_INT, 0, new_comm);
	MPI_Scatter(first_line, length * SIZE, MPI_INT, first_buffer, length * SIZE, MPI_INT, 0, new_comm);
	MPI_Scatter(second_line, length * SIZE, MPI_INT, second_buffer, length * SIZE, MPI_INT, 0, new_comm);
	for (int procNumber = 0; procNumber < number; procNumber++) {
		MPI_Cart_shift(new_comm, 0, 1, &source, &rank_dest);
		int p = ((rank + number - procNumber) % number) * length;
		for (int x = 0; x < length; x++) { for (int y = 0; y < SIZE; y++) 
				for (int z = p; z < p + length; z++)
					tmp[y + x * SIZE] += first_buffer[z + SIZE * x] * second_buffer[y + SIZE * (z - p)];

		}
		MPI_Sendrecv_replace(second_buffer, length * SIZE, MPI_INT, rank_dest, 0, source, 0, new_comm, &status);
	}
	MPI_Gather(tmp, length * SIZE, MPI_INT, result_line, length * SIZE, MPI_INT, 0, new_comm);
	if (rank == 0) {
		lineTo(result, SIZE, result_line);
		printf("\n\nResults\n");
		matrixprint(result, SIZE);
		printf("\n\nTime\t%f", MPI_Wtime() - time);
	}
	MPI_Finalize();
	return 0;
}
