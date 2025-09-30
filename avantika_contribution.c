#include <stdio.h>
#define MAX 20

typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;
    int waiting;
    int turnaround;
} Process;

// Function to print results
void printResults(Process p[], int n) {
    float total_wait = 0, total_tat = 0;
    printf("\nPID\tAT\tBT\tPRI\tWT\tTAT");
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               p[i].pid, p[i].arrival, p[i].burst, p[i].priority,
               p[i].waiting, p[i].turnaround);
        total_wait += p[i].waiting;
        total_tat += p[i].turnaround;
    }
    printf("\n\nAverage Waiting Time: %.2f", total_wait / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

// Priority Scheduling (used for each queue)
void priorityScheduling(Process p[], int n) {
    int time = 0, done = 0;
    int completed[MAX] = {0};
    while (done < n) {
        int idx = -1, bestPri = 1e9;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].arrival <= time && p[i].priority < bestPri) {
                bestPri = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        p[idx].waiting = time - p[idx].arrival;
        time += p[idx].burst;
        p[idx].turnaround = p[idx].waiting + p[idx].burst;
        completed[idx] = 1;
        done++;
    }
    printResults(p, n);
}

// Multilevel Queue Scheduling
void multilevelQueue(Process p[], int n) {
    Process q1[MAX], q2[MAX];
    int n1 = 0, n2 = 0;

    // Split processes into 2 queues based on PID (or any other logic)
    for (int i = 0; i < n; i++) {
        if (p[i].pid % 2 == 0) q1[n1++] = p[i]; // Queue 1
        else q2[n2++] = p[i];                   // Queue 2
    }

    printf("\n--- Queue 1 (Priority Scheduling) ---\n");
    priorityScheduling(q1, n1);

    printf("\n--- Queue 2 (Priority Scheduling) ---\n");
    priorityScheduling(q2, n2);
}

int main() {
    Process p[MAX];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival, Burst, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].waiting = p[i].turnaround = 0;
    }

    multilevelQueue(p, n);
    return 0;
}
