/* 5) Priority Scheduling (non-preemptive) */
void priorityScheduling(Process *orig) {
    Process *p = cloneList(orig);
    int n = countList(p), done = 0;
    int time = minArrival(p);
    while (done < n) {
        Process *best = NULL, *it = p;
        while (it) {
            if (!it->completed && it->arrival <= time) {
                if (!best || it->priority < best->priority || (it->priority == best->priority && it->arrival < best->arrival))
                    best = it;
            }
            it = it->next;
        }
        if (!best) { time++; continue; }
        best->waiting = time - best->arrival;
        time += best->burst;
        best->turnaround = best->waiting + best->burst;
        best->completed = 1; done++;
    }
    printf("\n--- Priority Scheduling Results ---\n");
    printResults(p);
    freeList(p);
}
