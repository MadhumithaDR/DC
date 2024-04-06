#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define max_rows 100000
#define send_data_tag 2001
#define return_data_tag 2002

int array[max_rows];

int main(int argc, char **argv) {
    long int sum, partial_sum;
    MPI_Status status;
    int my_id, num_procs, ierr, i, num_rows, root_process = 0;

    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (my_id == root_process) {
        printf("Please enter the number of numbers to sum: ");
        scanf("%i", &num_rows);

        if (num_rows > max_rows) {
            printf("Too many numbers.\n");
            exit(1);
        }

        for (i = 0; i < num_rows; i++) {
            array[i] = i + 1;
        }
    }
    
    ierr = MPI_Bcast(&num_rows, 1, MPI_INT, root_process, MPI_COMM_WORLD);

    // Scatter the array to all processes
    ierr = MPI_Scatter(array, num_rows / num_procs, MPI_INT, array, num_rows / num_procs, MPI_INT, root_process, MPI_COMM_WORLD);

    partial_sum = 0;
    for (i = 0; i < num_rows / num_procs; i++) {
        partial_sum += array[i];
    }
    
    //printf("\nProcess id: %d and partial sum: %d",my_id,partial_sum);

    // Reduce partial sums to the root process
    ierr = MPI_Reduce(&partial_sum, &sum, 1, MPI_LONG, MPI_SUM, root_process, MPI_COMM_WORLD);

    if (my_id == root_process) {
        printf("The grand total is: %i\n", sum);
    }

    ierr = MPI_Finalize();
    return 0;
}

