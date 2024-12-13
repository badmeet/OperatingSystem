#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct Process {
    int pid;            
    int arrival_time;   
    int burst_time;     
    int remaining_time; 
    int completion_time;
    int turnaround_time;
    int waiting_time;   
    bool completed;     
};

// Structure to store Gantt chart entries
struct GanttEntry {
    int pid;           // Process ID
    int start_time;    // Start time of this execution block
    int end_time;      // End time of this execution block
};

void calculateTimesWithGantt(struct Process processes[], int n, 
                           struct GanttEntry gantt[], int *gantt_size) {
    int current_time = 0;
    int completed = 0;
    *gantt_size = 0;
    int current_process = -1;  // Track currently running process
    
    // Initialize remaining time and completed status
    for(int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
    }
    
    while(completed != n) {
        int shortest = -1;
        int min_burst = INT_MAX;
        
        // Find process with minimum remaining time
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && 
                !processes[i].completed && 
                processes[i].remaining_time < min_burst) {
                min_burst = processes[i].remaining_time;
                shortest = i;
            }
        }
        
        // If no process found, increment time
        if(shortest == -1) {
            // Add idle time to Gantt chart if needed
            if(current_process != -2) {  // -2 represents idle time
                gantt[*gantt_size].pid = -1;  // -1 represents idle
                gantt[*gantt_size].start_time = current_time;
                current_process = -2;
            }
            current_time++;
            if(current_process == -2) {
                gantt[*gantt_size].end_time = current_time;
            }
            continue;
        }
        
        // If process changed, create new Gantt entry
        if(shortest != current_process) {
            if(*gantt_size > 0) {
                gantt[*gantt_size - 1].end_time = current_time;
            }
            gantt[*gantt_size].pid = processes[shortest].pid;
            gantt[*gantt_size].start_time = current_time;
            (*gantt_size)++;
            current_process = shortest;
        }
        
        // Reduce remaining time and update current time
        processes[shortest].remaining_time--;
        current_time++;
        
        // If process completed
        if(processes[shortest].remaining_time == 0) {
            completed++;
            processes[shortest].completed = true;
            processes[shortest].completion_time = current_time;
            processes[shortest].turnaround_time = 
                processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = 
                processes[shortest].turnaround_time - processes[shortest].burst_time;
            gantt[*gantt_size - 1].end_time = current_time;
            current_process = -1;
        }
    }
}

void displayGanttChart(struct GanttEntry gantt[], int size) {
    printf("\nGantt Chart:\n");
    
    // Print process IDs
    printf("|");
    for(int i = 0; i < size; i++) {
        if(gantt[i].pid == -1)
            printf("IDLE");
        else
            printf("P%d ", gantt[i].pid);
        printf("|");
    }
    printf("\n");
    
    // Print timeline
    printf("0");
    for(int i = 0; i < size; i++) {
        printf("   %d", gantt[i].end_time);
    }
    printf("\n");
}

void displayResults(struct Process processes[], int n) {
    float avg_turnaround = 0, avg_waiting = 0;
    
    printf("\nProcess Execution Details:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("----------------------------------------\n");
    
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time);
            
        avg_turnaround += processes[i].turnaround_time;
        avg_waiting += processes[i].waiting_time;
    }
    
    avg_turnaround /= n;
    avg_waiting /= n;
    
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround);
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    struct GanttEntry gantt[100];  // Assuming maximum 100 context switches
    int gantt_size;
    
    // Input process details
    for(int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter details for Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    calculateTimesWithGantt(processes, n, gantt, &gantt_size);
    displayGanttChart(gantt, gantt_size);
    displayResults(processes, n);
    
    return 0;
}