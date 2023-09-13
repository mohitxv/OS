#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } else if (pid > 0) {
        // Parent process
        printf("Parent process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    } else {
        // Error handling if fork fails
        printf("Fork failed\n");
        return 1;
    }

    return 0;
}
