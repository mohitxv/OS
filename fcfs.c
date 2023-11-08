#include <stdio.h>

// Define the maximum number of processes
#define MAX 50

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0; // Waiting time for first process is always 0

    // Calculating waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i-1] + wt[i-1];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime(int processes[], int n, int bt[]) {
    int wt[MAX], tat[MAX], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes   Burst Time   Waiting Time   Turn-Around Time\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf("   %d", (i+1));
        printf("       %d", bt[i]);
        printf("           %d", wt[i]);
        printf("               %d\n", tat[i]);
    }

    printf("Average waiting time = %.2f", (float)total_wt / n);
    printf("\nAverage turn-around time = %.2f\n", (float)total_tat / n);
}

int main() {
    int processes[MAX], n, burst_time[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i] = i+1;  // Process number starts from 1
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &burst_time[i]);
    }

    findavgTime(processes, n, burst_time);
    return 0;
}
