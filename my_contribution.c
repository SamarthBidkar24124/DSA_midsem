// SRTF 
void srtf(Process p[], int n) {
    int time = 0, done = 0;
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    while (done < n) {
        int idx = -1, minRT = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minRT) {
                minRT = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        p[idx].remaining--;
        time++;
        if (p[idx].remaining == 0) {
            done++;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }
    printResults(p, n);
}
