#include <stdio.h>

int main() {
    int n, m; // n = number of processes, m = number of resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int max[n][m], allocation[n][m], need[n][m], available[m];
   
    // Input maximum resource allocation for each process
    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocated resources for each process
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            // Calculate the need matrix
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Input available resources
    printf("Enter the available resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    int work[m], finish[n];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int safeSequence[n];
    int count = 0;
    int safe = 0;

    while (count < n) {
        safe = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    safeSequence[count] = i;
                    count++;
                    finish[i] = 1;
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safe = 1;
                }
            }
        }
        if (!safe) {
            printf("The system is not in a safe state!\n");
            break;
        }
    }

    if (safe) {
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);
            if (i < n - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    }

    return 0;
}
