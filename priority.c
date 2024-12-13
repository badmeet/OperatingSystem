#include <stdio.h>
#define MAX_PROCESSES 4
#define QUANTUM 30

typedef struct
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int startTime;
    int endTime;
    int isCompleted;
    int order;
} Process;

void calculateTurnaroundTime(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].turnaroundTime = p[i].endTime - p[i].arrivalTime;
    }
}

void calculateWaitingTime(Process p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
    }
}

void printResults(Process p[], int n)
{
    printf("\nProcess\tArrival\tBurst\tPriority\tStart\tEnd\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t\t%d\n", p[i].order, p[i].arrivalTime, p[i].burstTime,
               p[i].priority, p[i].startTime, p[i].endTime, p[i].turnaroundTime, p[i].waitingTime);
    }
}

double calculateAverageWaitingTime(Process p[], int n)
{
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += p[i].waitingTime;
    }
    return (double)totalWaitingTime / n;
}

double calculateAverageTurnaroundTime(Process p[], int n)
{
    int totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        totalTurnaroundTime += p[i].turnaroundTime;
    }
    return (double)totalTurnaroundTime / n;
}

void printGanttChart(Process p[], int n)
{
    printf("\nGantt Chart:\n");
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        printf("| P%d ", p[i].order);
        time = p[i].endTime;
    }
    printf("|\n");
    time = 0;
    printf("%d    ",time);
    for (int i = 0; i < n; i++)
    {
        time += p[i].burstTime;
        printf("%d    ", time);
    }
    printf("\n");
}

void priorityScheduling(Process p[], int n)
{
    int time = 0, completed = 0;
    int order = 1;
    while (completed < n)
    {
        int minPriority = 1e9, minIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrivalTime <= time && !p[i].isCompleted && p[i].priority < minPriority)
            {
                minPriority = p[i].priority;
                minIndex = i;
            }
        }
        if (minIndex != -1)
        {
            p[minIndex].startTime = time;
            p[minIndex].endTime = time + p[minIndex].burstTime;
            time += p[minIndex].burstTime;
            p[minIndex].isCompleted = 1;
            p[minIndex].order = order++; // Assign order of execution
            completed++;
        }
        else
        {
            time++;
        }
    }
    calculateTurnaroundTime(p, n);
    calculateWaitingTime(p, n);
    printResults(p, n);
    printGanttChart(p, n);
}

void resetProcesses(Process p[], Process original[], int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i] = original[i];
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = 0;
    }
}

int main()
{
    Process original[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    if (n > MAX_PROCESSES) {
        printf("Number of processes exceeds the maximum limit of %d.\n", MAX_PROCESSES);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d\n", i + 1);
        original[i].id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &original[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &original[i].burstTime);
        printf("Priority: ");
        scanf("%d", &original[i].priority);
        original[i].remainingTime = original[i].burstTime;
        original[i].isCompleted = 0;
    }

    Process p[MAX_PROCESSES];
    printf("\n--- Non-preemptive Priority Scheduling ---\n");
    resetProcesses(p, original, n);
    priorityScheduling(p, n);
    printf("Average Waiting Time (Priority): %.2f\n", calculateAverageWaitingTime(p, n));
    printf("Average Turnaround Time (Priority): %.2f\n", calculateAverageTurnaroundTime(p, n));

    return 0;
}
