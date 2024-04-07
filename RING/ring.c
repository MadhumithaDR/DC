#include <stdio.h>
#define MAX 10

int list[MAX], n, c;

void display() {
    printf("\nProcesses-->");
    for(int i = 1; i <= n; i++)
        printf("\t %d", i);
    
    printf("\nAlive-->");
    for(int i = 1; i <= n; i++)
        printf("\t %d", list[i]);
    
    printf("\nCoordinator is::%d", c);
}

void crash_process() {
    int crash, gid, subcdr;
    printf("\nEnter Process no. to Crash::");
    scanf("%d", &crash);
    
    if (list[crash])
        list[crash] = 0;
    else
        printf("\nProcess is already dead!!");
    
    do {
        printf("\nEnter election generator id::");
        scanf("%d", &gid);
        if (gid == c)
            printf("\nEnter a valid generator id::");
    } while (gid == crash);
    
    int msg[MAX], k = 1;
    if (crash == c) {
        msg[k++] = gid;
        for(int i = (gid + 1) % n; i != gid; i = (i + 1) % n) {
            if (list[i]) {
                printf("\nmessage is sent to %d k = %d", i, k);
                msg[k++] = i;
            }
        }
        subcdr = 0;
        for(int i = 1; i < k; i++) {
            printf("\nmsg::%d\n", msg[i]);
            if (subcdr < msg[i]) {
                subcdr = msg[i];
            }
        }
        c = subcdr;
    }
    
    display();
}

void activate_process() {
    int activate, subcdr;
    printf("\nEnter Process no. to Activate::");
    scanf("%d", &activate);
    
    if (!list[activate])
        list[activate] = 1;
    else
        printf("\nProcess is already alive!!");
    
    int flag = 0;
    if (activate == n)
        c = n;
    else {
        for(int i = activate + 1; i <= n; i++) {
            printf("\nmessage is sent from %d to %d", activate, i);
            if (list[i]) {
                subcdr = i;
                printf("\nResponse is sent from %d to %d", i, activate);
                flag = 1;
            }
        }
        if (flag == 1)
            c = subcdr;
        else
            c = activate;
    }
    
    display();
}

int main() {
    printf("\nEnter the number of processes::");
    scanf("%d", &n);
    
    for(int i = 1; i <= n; i++) {
        printf("Enter Process %d status (0/1)::", i);
        scanf("%d", &list[i]);
        
        if (list[i])
            c = i;
    }
    
    display();
    printf("\nRING ALGORITHM\n");

    int choice;
    do {
        printf("\n1. Crash a process\n2. Activate a process\n3. Display status\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                crash_process();
                break;
            case 2:
                activate_process();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
