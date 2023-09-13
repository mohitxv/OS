#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid, n, oddsum = 0, evensum = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    pid = fork();

    if (pid == 0) {
        // Child process
        for (int i = 1; i <= n; i += 2) {
            oddsum += i;
        }
        printf("Child: Sum of odd numbers up to %d is %d\n", n, oddsum);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        for (int i = 2; i <= n; i += 2) {
            evensum += i;
        }
        printf("Parent: Sum of even numbers up to %d is %d\n", n, evensum);
    } else {
        // Error handling if fork fails
        printf("Fork failed\n");
        return 1;
    }

    return 0;
}
