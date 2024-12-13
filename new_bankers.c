#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to check if the requested resources can be allocated
bool isSafe(int processes, int resources, int available[], int max[][MAX_RESOURCES],
            int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES], int safeSeq[]) {
    
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    int safeIndex = 0;
    
    // Initialize work array with available resources
    for(int i = 0; i < resources; i++)
        work[i] = available[i];
    
    // Find a process that can be allocated resources
    bool found;
    do {
        found = false;
        for(int p = 0; p < processes; p++) {
            if(finish[p] == false) {
                bool canAllocate = true;
                
                // Check if all resources can be allocated
                for(int r = 0; r < resources; r++) {
                    if(need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                
                // If we can allocate resources to this process
                if(canAllocate) {
                    // Add allocated resources back to work
                    for(int r = 0; r < resources; r++)
                        work[r] += allocation[p][r];
                    
                    // Add process to safe sequence and mark it finished
                    safeSeq[safeIndex++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
    } while(found);
    
    // Check if all processes are finished
    for(int i = 0; i < processes; i++)
        if(finish[i] == false)
            return false;
    
    return true;
}

int main() {
    int processes = 5;  // Number of processes
    int resources = 3;  // Number of resources
    
    // Available resources
    int available[MAX_RESOURCES] = {3, 3, 2};
    
    // Maximum resources that can be allocated to processes
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {4, 2, 2},
        {5, 3, 3}
    };
    
    // Resources currently allocated to processes
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    
    // Calculate need matrix
    int need[MAX_PROCESSES][MAX_RESOURCES];
    for(int i = 0; i < processes; i++)
        for(int j = 0; j < resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    
    // Array to store safe sequence
    int safeSeq[MAX_PROCESSES];
    
    printf("\nNeed Matrix:\n");
    for(int i = 0; i < processes; i++) {
        printf("P%d: ", i);
        for(int j = 0; j < resources; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
    
    if(isSafe(processes, resources, available, max, allocation, need, safeSeq)) {
        printf("\nSystem is in safe state.\nSafe sequence is: ");
        for(int i = 0; i < processes; i++)
            printf("P%d%s", safeSeq[i], (i == processes - 1) ? "\n" : " -> ");
    } else {
        printf("\nSystem is not in safe state!\n");
    }
    
    return 0;
}