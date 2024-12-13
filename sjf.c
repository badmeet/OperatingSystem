#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time
    int completion_time;// Completion time
    int turnaround_time;// Turnaround time
    int waiting_time;   // Waiting time
    int start_time;     // Start time for Gantt chart
    int is_completed;   // Flag to mark completion status
};

// Function to find the process with minimum burst time among available processes
int findShortestJob(struct Process processes[], int n, int current_time) {
    int min_burst = INT_MAX;
    int shortest_job_index = -1;
    
    for(int i = 0; i < n; i++) {
        if(processes[i].arrival_time <= current_time && 
            processes[i].is_completed == 0 && 
            processes[i].burst_time < min_burst) {
            min_burst = processes[i].burst_time;
            shortest_job_index = i;
        }
    }
    
    return shortest_job_index;
}

// Function to calculate completion, turnaround, and waiting times
void calculateTimes(struct Process processes[], int n) {
    int completed = 0;
    int current_time = 0;
    
    // Initialize is_completed flag for all processes
    for(int i = 0; i < n; i++) {
        processes[i].is_completed = 0;
    }
    
    // Process until all processes are completed
    while(completed < n) {
        // Find process with minimum burst time among available processes
        int shortest_job_index = findShortestJob(processes, n, current_time);
        
        if(shortest_job_index == -1) {
            current_time++;
            continue;
        }
        
        // Update process times
        processes[shortest_job_index].start_time = current_time;
        processes[shortest_job_index].completion_time = current_time + processes[shortest_job_index].burst_time;
        processes[shortest_job_index].turnaround_time = processes[shortest_job_index].completion_time - 
                                                        processes[shortest_job_index].arrival_time;
        processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - 
                                                    processes[shortest_job_index].burst_time;
        
        // Mark process as completed and update counters
        processes[shortest_job_index].is_completed = 1;
        completed++;
        current_time = processes[shortest_job_index].completion_time;
    }
}

// Function to draw Gantt chart
void drawGanttChart(struct Process processes[], int n) {
    // Sort processes by start time for Gantt chart
    struct Process temp;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(processes[j].start_time > processes[j+1].start_time) {
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
    
    printf("\nGantt Chart:\n\n");

    printf("\n|");
    
    // Print process IDs
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < processes[i].burst_time - 1; j++) 
            printf(" ");
        printf("P%d", processes[i].pid);
        for(int j = 0; j < processes[i].burst_time - 1; j++) 
            printf(" ");
        printf("|");
    }
    printf("\n ");
    
    // Print timeline
    printf("%d",processes[0].start_time);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < processes[i].burst_time; j++) 
            printf(" ");
        printf("%d", processes[i].completion_time);
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