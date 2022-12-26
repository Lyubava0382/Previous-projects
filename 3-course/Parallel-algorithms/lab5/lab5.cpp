#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#define MAX_LENGTH 1000

int main(int argc, char* argv[])
{
	double time_start;
	int size, rank, n,a_resv, newrank, new_a;
	MPI_Status status;
	MPI_Comm newcomm;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int a = rank + 1;
	int* index = new int[size];
	int* edges = new int[size - 1];
	int count = 0;
	time_start = MPI_Wtime();
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			index[0] = 2;
		}
		else if (i == size - 2) {
			index[count] = index[count - 1] + 2;
		}
		else if (i % 2 == 0) {
			index[count] = index[count - 1] + 3;
		}
		else {
			index[count] = index[count - 1] + 1;
		}
		count++;
	}
	
	count = 0;
	for (int i = 0; i < size; i++) {
		if (i % 2 != 0) {
			edges[count] = i - 1;
			count++;
		}
		else {
			edges[count] = i + 1;
			count++;
			if (i - 2 >= 0) {
				edges[count] = i - 2;
				count++;
			}
			if (i + 2 < size - 1) {
				edges[count] = i + 2;
				count++;
			}
		}	
	}
	int number_of_neighbours_retrieved;
	MPI_Graph_create(MPI_COMM_WORLD, size, index, edges, false, &newcomm);
	MPI_Graph_neighbors_count(newcomm, rank, &number_of_neighbours_retrieved);
	int* neighbours_retrieved = new int[number_of_neighbours_retrieved];
	MPI_Graph_neighbors(newcomm, rank, number_of_neighbours_retrieved, neighbours_retrieved);
	for (int n = 0; n < number_of_neighbours_retrieved; n++) { 
		MPI_Sendrecv(&a, 1, MPI_INT, neighbours_retrieved[n], 1,
			&a_resv, 1, MPI_INT, neighbours_retrieved[n], 1, newcomm, &status);
		printf("rank = %d, resv a = %d, from %d\n", rank, a_resv, neighbours_retrieved[n]);
	}
	MPI_Finalize();
	return 0;
}
