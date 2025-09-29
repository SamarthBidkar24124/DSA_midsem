Round Robin
void roundRobin(Process p[], int n, int tq) {
    int time = 0, done = 0;
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    while (done < n) {
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                flag = 1;
                if (p[i].remaining <= tq) {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    done++;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                } else {
                    p[i].remaining -= tq;
                    time += tq;
                }
            }
        }
        if (!flag) time++;
    }
    printResults(p, n);
}
