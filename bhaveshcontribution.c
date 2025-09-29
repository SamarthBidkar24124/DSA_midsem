//Priority Scheduling (Non-preemptive)
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
