#include <stdio.h>
#include <limits.h>

#define MAX_BLOCKS 100
#define MAX_PROCESS 100

// Function to initialize memory blocks and processes
void initializeArrays(int blocks[], int processes[], int n, int m) {
    printf("\nEnter the size of memory blocks:\n");
    for(int i = 0; i < n; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }
    
    printf("\nEnter the size of processes:\n");
    for(int i = 0; i < m; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }
}

// First Fit Algorithm
void firstFit(int blocks[], int processes[], int n, int m) {
    int allocation[MAX_PROCESS];
    int occupied[MAX_BLOCKS] = {0};
    
    // Initialize allocation array with -1
    for(int i = 0; i < m; i++)
        allocation[i] = -1;
    
    // Allocate memory to processes using First Fit
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(!occupied[j] && blocks[j] >= processes[i]) {
                allocation[i] = j;
                occupied[j] = 1;
                break;
            }
        }
    }
    
    // Print allocation details
    printf("\nFirst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < m; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Best Fit Algorithm
void bestFit(int blocks[], int processes[], int n, int m) {
    int allocation[MAX_PROCESS];
    int occupied[MAX_BLOCKS] = {0};
    
    // Initialize allocation array with -1
    for(int i = 0; i < m; i++)
        allocation[i] = -1;
    
    // Allocate memory to processes using Best Fit
    // for(int i = 0; i < m; i++) {
    //     int bestIdx = -1;
    //     int minDiff = INT_MAX;
        
    //     for(int j = 0; j < n; j++) {
    //         if(!occupied[j] && blocks[j] >= processes[i]) {
    //             if(blocks[j] - processes[i] < minDiff) {
    //                 bestIdx = j;
    //                 minDiff = blocks[j] - processes[i];
    //             }
    //         }
    //     }
        
    //     if(bestIdx != -1) {
    //         allocation[i] = bestIdx;
    //         occupied[bestIdx] = 1;
    //     }
    // }
    for(int i = 0; i < m; i++){
        int best = INT_MAX;
        int idx = -1;
        for(int j = 0; j < n; j++){
            if(!occupied[j] && blocks[j] >= processes[i]){
                if(blocks[j] < best){
                    best = blocks[j];
                    idx = j;
                }
            }
        }
        
        if(idx != -1){
            occupied[idx] = 1;
            allocation[i] = idx;
        }
    }
    
    // Print allocation details
    printf("\nBest Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < m; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Worst Fit Algorithm
void worstFit(int blocks[], int processes[], int n, int m) {
    int allocation[MAX_PROCESS];
    int occupied[MAX_BLOCKS] = {0};
    
    // Initialize allocation array with -1
    for(int i = 0; i < m; i++)
        allocation[i] = -1;
    
    // Allocate memory to processes using Worst Fit
    // for(int i = 0; i < m; i++) {
    //     int worstIdx = -1;
    //     int maxDiff = -1;
        
    //     for(int j = 0; j < n; j++) {
    //         if(!occupied[j] && blocks[j] >= processes[i]) {
    //             if(blocks[j] - processes[i] > maxDiff) {
    //                 worstIdx = j;
    //                 maxDiff = blocks[j] - processes[i];
    //             }
    //         }
    //     }
        
    //     if(worstIdx != -1) {
    //         allocation[i] = worstIdx;
    //         occupied[worstIdx] = 1;
    //     }
    // }
    for(int i = 0; i < m; i++){
        int best = INT_MIN;
        int idx = -1;
        for(int j = 0; j < n; j++){
            if(!occupied[j] && blocks[j] >= processes[i]){
                if(blocks[j] > best){
                    best = blocks[j];
                    idx = j;
                }
            }
        }
        
        if(idx != -1){
            occupied[idx] = 1;
            allocation[i] = idx;
        }
    }
    
    // Print allocation details
    printf("\nWorst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < m; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blocks[MAX_BLOCKS], processes[MAX_PROCESS];
    int n, m; // n: number of blocks, m: number of processes
    
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);
    printf("Enter the number of processes: ");
    scanf("%d", &m);
    
    initializeArrays(blocks, processes, n, m);
    
    // Perform all three allocation strategies
    firstFit(blocks, processes, n, m);
    bestFit(blocks, processes, n, m);
    worstFit(blocks, processes, n, m);
    
    return 0;
}