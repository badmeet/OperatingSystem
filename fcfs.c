#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time
    int completion_time;// Completion time
    int turnaround_time;// Turnaround time
    int waiting_time;   // Waiting time
    int start_time;     // Start time for Gantt chart
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort processes by arrival time
void sortByArrivalTime(struct Process processes[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(processes[j].arrival_time > processes[j+1].arrival_time) {
                swap(&processes[j], &processes[j+1]);
            }
        }
    }
}

// Function to calculate completion, turnaround, and waiting times
void calculateTimes(struct Process processes[], int n) {
    int current_time = 0;
    
    for(int i = 0; i < n; i++) {
        if(current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        processes[i].start_time = current_time;
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

// Function to draw Gantt chart
void drawGanttChart(struct Process processes[], int n) {
    int total_time = processes[n-1].completion_time;
    int scale_factor = 1;
    
    // Adjust scale factor if total time is too large
    if(total_time > 50) {
        scale_factor = (total_time / 50) + 1;
    }
    printf("|");
    
    // Print process IDs
    for(int i = 0; i < n; i++) {
        int duration = processes[i].burst_time;
        for(int j = 0; j < duration/scale_factor - 1; j++){
            printf(" ");
        }
        printf("P%d", processes[i].pid);
        for(int j = 0; j < duration/scale_factor - 1; j++){
            printf(" ");
        }
        printf("|");
    }
    printf("\n");

    printf("%d ",processes[0].start_time);
    int current_time = 0;
    for(int i = 0; i < n; i++) {
        int duration = processes[i].burst_time;
        for(int j = 0; j < duration/scale_factor; j++){
            printf(" ");
        }
        current_time = processes[i].completion_time;
        printf("%d   ", current_time);
    }
    printf("\n");
}

int main() {
    int n;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    // Input process details
    for(int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nFor Process %d:\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    // Sort processes by arrival time
    sortByArrivalTime(processes, n);
    
    // Calculate times
    calculateTimes(processes, n);
    
    // Print process details
    printf("\nPID\tArrival\tBurst\tStart\tCompletion\tTurnaround\tWaiting\n");
    printf("-------------------------------------------------------------------------\n");
    
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].start_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time);
            
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    
    // Calculate and print average times
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    
    // Draw Gantt chart
    drawGanttChart(processes, n);
    
    return 0;
}