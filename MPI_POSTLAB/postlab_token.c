#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int my_rank, num_procs;
    int token = 10;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (my_rank == 0) {
    	MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    	printf("Process %d sent token: %d\n", my_rank, token);
    } else {
    	MPI_Recv(&token, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    	printf("Process %d received token: %d\n", my_rank, token);
    	if (my_rank != num_procs - 1) {
    		MPI_Send(&token, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
                printf("Process %d sent token: %d\n", my_rank, token);
        }
        else{
        	MPI_Send(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                printf("Process %d sent token: %d\n", my_rank, token);
        }
    }
    MPI_Finalize();
    return 0;
}

