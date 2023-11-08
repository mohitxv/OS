#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;             // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time
    int waiting_time;   // Waiting time
    int turnaround_time; // Turnaround time
};

// Function to calculate the average waiting time and average turnaround time
void calculateAverageTimes(struct Process processes[], int n) {
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Calculate and print average waiting time and average turnaround time
    float average_waiting_time = total_waiting_time / n;
    float average_turnaround_time = total_turnaround_time / n;

    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = malloc(sizeof(struct Process) * n);
    if (processes == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Exit with an error code
    }

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].waiting_time = 0;   // Initialize waiting time
        processes[i].turnaround_time = 0; // Initialize turnaround time
    }

    // Sort processes based on arrival time (FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    // Print process details, waiting time, and turnaround time
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Calculate and print average waiting time and average turnaround time
    calculateAverageTimes(processes, n);

    // Free dynamically allocated memory
    free(processes);

    return 0;
}
