#include <stdio.h>

#define MAX_PROCESSES 10

// Function to detect deadlock
int detect_deadlock(int processes, int allocation[MAX_PROCESSES][MAX_PROCESSES], int request[MAX_PROCESSES][MAX_PROCESSES]) {
    int i, j, k;
    int finish[MAX_PROCESSES] = {0}; // Initialize all processes as unfinished
    int work[MAX_PROCESSES];

    // Initialize work as 0
    for (i = 0; i < processes; ++i)
        work[i] = 0;

    // Find the finish status of each process
    for (i = 0; i < processes; ++i) {
        if (!finish[i]) {
            int can_allocate = 1;
            for (j = 0; j < processes; ++j) {
                if (request[i][j] > work[j]) {
                    can_allocate = 0;
                    break;
                }
            }

            if (can_allocate) {
                finish[i] = 1;
                for (j = 0; j < processes; ++j)
                    work[j] += allocation[i][j];
                i = -1; // Restart loop to recheck all processes
            }
        }
    }

    // If all processes finished, no deadlock
    for (i = 0; i < processes; ++i) {
        if (!finish[i]) {
            return 1; // Deadlock detected
        }
    }

    return 0; // No deadlock detected
}

int main() {
    int processes;
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    int allocation[MAX_PROCESSES][MAX_PROCESSES];
    int request[MAX_PROCESSES][MAX_PROCESSES];

    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < processes; ++j)
            scanf("%d", &allocation[i][j]);
    }

    // Input request matrix
    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; ++i) {
        printf("For process %d: ", i);
        for (int j = 0; j < processes; ++j)
            scanf("%d", &request[i][j]);
    }

    // Detect deadlock
    if (detect_deadlock(processes, allocation, request))
        printf("Deadlock detected.\n");
    else
        printf("No deadlock detected.\n");

    return 0;
}
