#include <stdio.h>
#include <stdbool.h>

// Define the maximum number of processes
#define MAX 50

typedef struct {
    int pid;
    int burst_time;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcessesByBurstTime(Process p[], int n) {
    // Simple bubble sort based on burst time
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].burst_time > p[j+1].burst_time) {
                swap(&p[j], &p[j+1]);
            }
        }
    }
}

void findWaitingAndTurnaroundTime(Process p[], int n, int wt[], int tat[]) {
    wt[0] = 0;
    tat[0] = p[0].burst_time;

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i-1] + p[i-1].burst_time;
        tat[i] = wt[i] + p[i].burst_time;
    }
}

void findAverageTime(Process p[], int n) {
    int wt[MAX], tat[MAX];
    int total_wt = 0, total_tat = 0;

    sortProcessesByBurstTime(p, n);

    findWaitingAndTurnaroundTime(p, n, wt, tat);

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt/n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat/n);
}

int main() {
    int n;
    Process p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &p[i].burst_time);
    }

    findAverageTime(p, n);
    return 0;
}
