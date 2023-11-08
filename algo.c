#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4

int memory[MEMORY_SIZE]; // Memory to store pages
int pageTable[MEMORY_SIZE]; // Page table to keep track of pages in memory
int pageReferences[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}; // Example page references

int fifoReplace(int* memory, int* pageTable, int page, int pointer) {
    // Check if the page at the current pointer is already occupied
    if (memory[pointer] != -1) {
        // Mark the page in the page table as not in memory
        pageTable[memory[pointer]] = 0;
    }

    // Place the new page in memory and update the page table
    memory[pointer] = page;
    pageTable[page] = 1;

    // Move the pointer to the next location in a circular manner
    pointer = (pointer + 1) % MEMORY_SIZE;

    return pointer;
}


int lruReplace(int* memory, int* pageTable, int page) {
    int leastRecentlyUsedIndex = 0;
    int leastRecentlyUsedTime = pageTable[memory[0]];

    // Find the least recently used page in memory
    for (int i = 1; i < MEMORY_SIZE; i++) {
        if (pageTable[memory[i]] < leastRecentlyUsedTime) {
            leastRecentlyUsedIndex = i;
            leastRecentlyUsedTime = pageTable[memory[i]];
        }
    }

    // Mark the least recently used page as not in memory
    pageTable[memory[leastRecentlyUsedIndex]] = 0;

    // Place the new page in memory and update the page table
    memory[leastRecentlyUsedIndex] = page;
    pageTable[page] = 1;

    return leastRecentlyUsedIndex;
}

int lfuReplace(int* memory, int* pageTable, int page) {
    int leastFrequentlyUsedIndex = 0;
    int leastFrequentlyUsedCount = pageTable[memory[0]];

    // Find the least frequently used page in memory
    for (int i = 1; i < MEMORY_SIZE; i++) {
        if (pageTable[memory[i]] < leastFrequentlyUsedCount) {
            leastFrequentlyUsedIndex = i;
            leastFrequentlyUsedCount = pageTable[memory[i]];
        }
    }

    // Mark the least frequently used page as not in memory
    pageTable[memory[leastFrequentlyUsedIndex]] = 0;

    // Place the new page in memory and update the page table
    memory[leastFrequentlyUsedIndex] = page;
    pageTable[page] = 1;

    return leastFrequentlyUsedIndex;
}


void printMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

int main() {
    int pageHits = 0;
    int pageMisses = 0;
    int pointer = 0; // Pointer for FIFO

    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = -1; // Initialize memory with an invalid value
    }

    for (int i = 0; i < sizeof(pageReferences) / sizeof(pageReferences[0]); i++) {
        int page = pageReferences[i];

        if (pageTable[page] == 1) {
            pageHits++;
        } else {
            pageMisses++;
            // Call the respective replacement function (e.g., fifoReplace, lruReplace, or lfuReplace)
            // Update memory and page table
        }

        printMemory();
    }

    printf("Page Hits: %d\n", pageHits);
    printf("Page Misses: %d\n", pageMisses);

    return 0;
}
