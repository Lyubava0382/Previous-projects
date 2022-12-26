#include <stdio.h>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#define MAX_LENGTH 10

int main(int argc, char* argv[])
{
	srand(time(0));
	double time_start, time;
	int size, rank, count = 0, index = 0, index_res = 0;
	double double_x;
	MPI_Status status;
	int* array = new int[MAX_LENGTH];
	int* result = new int[MAX_LENGTH];
	int* message;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int* random = new int[size];

	MPI_Request req;
	time_start = MPI_Wtime();
	if ( rank == 0 && rank < size) {
		for (int i = 1; i < size; ++i)
			random[i - 1] = i;
		for (int i = 0; i < size - 1; ++i)
		{
			int temp = random[i];
			int for_rand = rand() % (size - 1);
			random[i] = random[for_rand];
			random[for_rand] = temp;
		}
		for (int i = 0; i < MAX_LENGTH; i++) {
			array[i] = rand() % 100;
		}
		if (size <= 2) count = MAX_LENGTH;
		else {
			double summ = 0;
			for (int x = 1; x < size; x++) {
				summ += double(1)/x;
			}
			count = round(MAX_LENGTH / summ);
		}
		for (int i = 0; i < size - 1; ++i) {
			message = (int*)(calloc(MAX_LENGTH, sizeof(int)));
			for (int k = 0; k < MAX_LENGTH; k++) {
				if (k < count) message[k] = array[index++];
				else { 
					if (count == 0 && index < MAX_LENGTH)
					message[k] = array[index++];
					else message[k] = -1;
				}
			}
			MPI_Isend(message, MAX_LENGTH, MPI_INT, random[i],
				0, MPI_COMM_WORLD, &req);
				MPI_Recv(message, MAX_LENGTH, MPI_INT, random[i], 0, MPI_COMM_WORLD,
				&status);
			for (int t = 0; t < count && message[t] >= 0; t++) {
				result[index_res] = message[t];
				index_res++;
			}
			count = round(count / 2);
		}
		for (int res = index_res; res < MAX_LENGTH; res++) result[res] = -1;
		for (int t = 0; t < MAX_LENGTH && result[t] >= 0; t++) {
			printf("\nprocess %d, result[%d] = %d", rank, t, result[t]);
		}
	}
	else if (rank > 0) {
		message = new int[MAX_LENGTH];
		MPI_Recv(message, MAX_LENGTH, MPI_INT, 0, 0, MPI_COMM_WORLD,
			&status);
		int temp; 
		for (int i = 0; i < MAX_LENGTH - 1; i++) {
			for (int j = 0; j < MAX_LENGTH - i - 1; j++) {
				if (message[j] > message[j + 1] && message[j] >= 0 && message[j + 1] >= 0) {
					temp = message[j];
					message[j] = message[j + 1];
					message[j + 1] = temp;
				}
			}
		}
				printf("\nprocess %d Sorted part of the array", rank);
			for (int t = 0; t < MAX_LENGTH && message[t] >= 0; t++)
				printf("\nmessage[%d] = %d", t, message[t]);
		
		MPI_Isend(message, MAX_LENGTH, MPI_INT, 0,
			0, MPI_COMM_WORLD, &req);
	}
	MPI_Finalize();
	return 0;
}
