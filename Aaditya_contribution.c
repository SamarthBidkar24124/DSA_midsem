/* 3) SRTF (preemptive) */
void srtf(Process *orig) {
    Process *p = cloneList(orig);
    int n = countList(p), done = 0;
    int time = minArrival(p);
    Process *it = p;
    while (it) { it->remaining = it->burst; it->completed = 0; it = it->next; }

    while (done < n) {
        Process *best = NULL; int minRem = INT_MAX;
        it = p;
        while (it) {
            if (!it->completed && it->arrival <= time && it->remaining > 0) {
                if (it->remaining < minRem) { minRem = it->remaining; best = it; }
            }
            it = it->next;
        }
        if (!best) { time++; continue; }
        best->remaining--; time++;
        if (best->remaining == 0) {
            best->completed = 1; done++;
            best->turnaround = time - best->arrival;
            best->waiting = best->turnaround - best->burst;
        }
    }

    printf("\n--- SRTF Results ---\n");
    printResults(p);
    freeList(p);
}
