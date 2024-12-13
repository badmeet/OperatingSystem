//FCFS -- FIRST COME FIRST SERVE NON-PREEMPTIVE IN C LANGUAGE

#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;         
    int arrival_time;   
    int burst_time;    
    int completion_time;
    int turnaround_time;
    int waiting_time;   
    int start_time;     
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortByArrivalTime(struct Process processes[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(processes[j].arrival_time > processes[j+1].arrival_time) {
                swap(&processes[j], &processes[j+1]);
            }
        }
    }
}

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

void drawGanttChart(struct Process processes[], int n) {
    int total_time = processes[n-1].completion_time;
    int scale_factor = 1;
    
    if(total_time > 50) {
        scale_factor = (total_time / 50) + 1;
    }
    printf("|");
    
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
    
    for(int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nFor Process %d:\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }
    
    sortByArrivalTime(processes, n);
    
    calculateTimes(processes, n);
    
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
    
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    
    drawGanttChart(processes, n);
    
    return 0;
}
