#include <stdio.h>

#define MEMORY_SIZE 50

int memory[MEMORY_SIZE];
int memorySize = MEMORY_SIZE;

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = -1; // -1 indicates that the memory is free
    }
}

void displayMemory() {
    for (int i = 0; i < memorySize; i++) {
        if (memory[i] == -1) {
            printf("_ ");
        } else {
            printf("%d ", memory[i]);
        }
    }
    printf("\n");
}

// First Fit Allocation
int firstFit(int processSize) {
    for (int i = 0; i < memorySize; i++) {
        if (memory[i] == -1 && i + processSize <= memorySize) {
            for (int j = i; j < i + processSize; j++) {
                memory[j] = processSize;
            }
            return i;
        }
    }
    return -1; // Memory allocation failed
}

// Best Fit Allocation
int bestFit(int processSize) {
    int bestFitIdx = -1;
    int bestFitSize = memorySize + 1;

    for (int i = 0; i < memorySize; i++) {
        if (memory[i] == -1) {
            int blockSize = 0;
            int j = i;
            while (memory[j] == -1 && j < memorySize) {
                blockSize++;
                j++;
            }

            if (blockSize >= processSize && blockSize < bestFitSize) {
                bestFitSize = blockSize;
                bestFitIdx = i;
            }
        }
    }

    if (bestFitIdx != -1) {
        for (int i = bestFitIdx; i < bestFitIdx + processSize; i++) {
            memory[i] = processSize;
        }
    }

    return bestFitIdx;
}

// Worst Fit Allocation
int worstFit(int processSize) {
    int worstFitIdx = -1;
    int worstFitSize = -1;

    for (int i = 0; i < memorySize; i++) {
        if (memory[i] == -1) {
            int blockSize = 0;
            int j = i;
            while (memory[j] == -1 && j < memorySize) {
                blockSize++;
                j++;
            }

            if (blockSize >= processSize && blockSize > worstFitSize) {
                worstFitSize = blockSize;
                worstFitIdx = i;
            }
        }
    }

    if (worstFitIdx != -1) {
        for (int i = worstFitIdx; i < worstFitIdx + processSize; i++) {
            memory[i] = processSize;
        }
    }

    return worstFitIdx;
}

int main() {
    initializeMemory();

    int processSizes[] = {20, 10, 30, 5, 15};
    int numProcesses = sizeof(processSizes) / sizeof(processSizes[0]);

    printf("Initial Memory State:\n");
    displayMemory();

    for (int i = 0; i < numProcesses; i++) {
        int firstFitIdx = firstFit(processSizes[i]);
        if (firstFitIdx != -1) {
            printf("Allocated Process %d using First Fit at position %d\n", i + 1, firstFitIdx);
        } else {
            printf("Process %d allocation failed using First Fit\n", i + 1);
        }
    }

    printf("\nMemory State After First Fit Allocation:\n");
    displayMemory();

    initializeMemory(); // Reset memory for the next allocation method

    for (int i = 0; i < numProcesses; i++) {
        int bestFitIdx = bestFit(processSizes[i]);
        if (bestFitIdx != -1) {
            printf("Allocated Process %d using Best Fit at position %d\n", i + 1, bestFitIdx);
        } else {
            printf("Process %d allocation failed using Best Fit\n", i + 1);
        }
    }

    printf("\nMemory State After Best Fit Allocation:\n");
    displayMemory();

    initializeMemory(); // Reset memory for the next allocation method

    for (int i = 0; i < numProcesses; i++) {
        int worstFitIdx = worstFit(processSizes[i]);
        if (worstFitIdx != -1) {
            printf("Allocated Process %d using Worst Fit at position %d\n", i + 1, worstFitIdx);
        } else {
            printf("Process %d allocation failed using Worst Fit\n", i + 1);
        }
    }

    printf("\nMemory State After Worst Fit Allocation:\n");
    displayMemory();

    return 0;
}
