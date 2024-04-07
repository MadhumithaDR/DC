#include<stdio.h>
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
    int crash;
    printf("\nEnter Process no. to Crash::");
    scanf("%d", &crash);
   
    if (list[crash])
        list[crash] = 0;
    else
        printf("\nProcess is already dead!!");
   
    int gid;
    do {
        printf("\nEnter election generator id::");
        scanf("%d", &gid);
        if (gid == c)
            printf("\nEnter a valid generator id::");
    } while (gid == crash);
   
    int flag = 0, subcdr;
    if (crash == c) {
        for(int i = gid + 1; i <= n; i++) {
            printf("\nmessage is sent from %d to %d", gid, i);
            if (list[i]) {
                subcdr = i;
                printf("Response is sent from %d to %d", i, gid);
                flag = 1;
            }
        }
       
        if (flag == 1)
            c = subcdr;
        else
            c = gid;
    }
   
    display();
}

void activate_process() {
    int activate;
    printf("\nEnter Process no. to Activate::");
    scanf("%d", &activate);
   
    if (!list[activate])
        list[activate] = 1;
    else
        printf("\nProcess is already alive!!");
   
    int flag = 0, subcdr;
    if (activate == n)
        c = n;
    else {
        for(int i = activate + 1; i <= n; i++) {
            printf("\nmessage is sent from %d to %d", activate, i);
            if (list[i]) {
                subcdr = i;
                printf("Response is sent from %d to %d", i, activate);
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
    printf("\nBULLY ALGORITHM\n");

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
