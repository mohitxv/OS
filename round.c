#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int pid; // Process ID
    int burst_time; // Burst time
    int remaining_time; // Remaining time
};

int main() {
    int n, quantum;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[MAX_PROCESS];
    
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    int time = 0;
    
    printf("\nGantt Chart:\n");
    
    while (1) {
        int done = 1; // Flag to check if all processes are done
        
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                done = 0; // There are unfinished processes
                
                // Execute the process for the time quantum or the remaining time, whichever is smaller
                int execute_time = (processes[i].remaining_time < quantum) ? processes[i].remaining_time : quantum;
                processes[i].remaining_time -= execute_time;
                
                printf("| P%d ", processes[i].pid);
                time += execute_time;
                
                // Display remaining time for each process
                for (int j = 0; j < n; j++) {
                    if (processes[j].remaining_time > 0) {
                        printf("| P%d ", processes[j].pid);
                    }
                }
                
                printf("|");
            }
        }
        
        if (done)
            break; // All processes are done
        
    }
    
    printf("\n\n");
    
    return 0;
}
