#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define max 100
int gnatt[max];
int g_idx = 0;

struct Process{
    int ppid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int remaining;
};

int find_shortest(struct Process process[], int n, int time){
    int idx = -1;
    int ans = INT_MAX;

    for(int i = 0; i < n; i++){
        if(process[i].at <= time && process[i].remaining != 0){
            if(process[i].remaining < ans){
                ans = process[i].remaining;
                idx = i;
            }
        }
    }

    return idx;
}

void calculateTimes(struct Process process[], int n){
    int current_time = 0;
    int completed = 0;

    while(completed < n){
        int idx = find_shortest(process, n, current_time);
        if(idx == -1){
            gnatt[g_idx++] = -1;
            current_time++;
        }
        else{
            gnatt[g_idx++] = process[idx].ppid;
            process[idx].remaining--;
            if(process[idx].remaining == 0){
                process[idx].ct = current_time+1;
                process[idx].tat = process[idx].ct - process[idx].at;
                process[idx].wt = process[idx].tat - process[idx].bt;
                completed++;
            }
        }
        current_time++;
    }
}

int main(){
    printf("Enter the no of process : ");
    int n;
    scanf("%d",&n);

    printf("\n");

    struct Process process[n];

    for(int i = 0; i < n; i++){
        process[i].ppid = i+1;
        printf("Enter arrival time of process %d : ",i+1);
        scanf("%d",&process[i].at);
        printf("Enter burst time of process %d : ",i+1);
        scanf("%d",&process[i].bt);
        process[i].remaining = process[i].bt;
        printf("\n");
    }

    calculateTimes(process, n);

    printf("AT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\n",process[i].at,
        process[i].bt,process[i].ct,process[i].tat,process[i].wt);
    }

    for(int i = 0; i < g_idx; i++){
        printf("P%d ",gnatt[i]);
    }
}