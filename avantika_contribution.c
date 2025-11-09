// 6) Multilevel Queue
void multilevelQueue(Process *orig, int tq) {
    Process *p = cloneList(orig);
    Process *q1 = NULL, *q2 = NULL;
    int cutoff = 3; // priority <= cutoff -> q1 (higher priority)
    Process *it = p;
    while (it) {
        if (it->priority <= cutoff) q1 = append(q1, newProc(it->pid, it->arrival, it->burst, it->priority));
        else q2 = append(q2, newProc(it->pid, it->arrival, it->burst, it->priority));
        it = it->next;
    }

    printf("\n--- Multilevel Queue: Queue1 (Priority) ---\n");
    if (q1) priorityScheduling(q1); else printf("(empty)\n");
    printf("\n--- Multilevel Queue: Queue2 (Round Robin) ---\n");
    if (q2) roundRobin(q2, tq); else printf("(empty)\n");

    freeList(p);
    freeList(q1);
    freeList(q2);
}
// 7) MLFQ: two-level multilevel feedback queue (L1 then L2)
void mlfq(Process *orig, int tq1, int tq2) {
    if (tq1 <= 0 || tq2 <= 0) { printf("Quanta must be > 0\n"); return; }
    Process *p = cloneList(orig);
    int n = countList(p), done = 0;
    int time = minArrival(p);
    Process *it = p;
    while (it) { it->remaining = it->burst; it->completed = 0; it->inqueue = 0; it = it->next; }

    Queue *L1 = createQ();
    Queue *L2 = createQ();

    it = p;
    while (it) {
        if (it->arrival <= time && it->remaining > 0) {
            enqueue(L1, it);
            it->inqueue = 1;
        }
        it = it->next;
    }

    while (done < n) {
        Process *cur = NULL;
        int cameFrom = 0; // 1 -> L1, 2 -> L2
        if (!qempty(L1)) { cur = dequeue(L1); cur->inqueue = 0; cameFrom = 1; }
        else if (!qempty(L2)) { cur = dequeue(L2); cur->inqueue = 0; cameFrom = 2; }
        else {
            int nxt = INT_MAX;
            it = p;
            while (it) {
                if (!it->completed && !it->inqueue && it->remaining > 0) {
                   if (nxt == INT_MAX || it->arrival < nxt) nxt = it->arrival;
                }
                it = it->next;
            }
            if (nxt == INT_MAX) break;
            
            if (nxt > time) time = nxt;
            else if (qempty(L1) && qempty(L2)) time = nxt; // Handle initial gap
            else time++; 

            it = p;
            while (it) {
                if (!it->inqueue && it->arrival <= time && it->remaining > 0) {
                    enqueue(L1, it);
                    it->inqueue = 1;
                }
                it = it->next;
            }
            continue;
        }

        int exec = 0;
        if (cameFrom == 1) exec = (cur->remaining <= tq1) ? cur->remaining : tq1;
        else exec = (cur->remaining <= tq2) ? cur->remaining : tq2;

        cur->remaining -= exec;
        time += exec;

        if (cur->remaining > 0) {
            if (cameFrom == 1 && exec == tq1) {
                enqueue(L2, cur);
                cur->inqueue = 1;
            } else if (cameFrom == 1) { // Did not use full tq1
                enqueue(L1, cur); 
                cur->inqueue = 1;
            } else { // cameFrom == 2
                enqueue(L2, cur);
                cur->inqueue = 1;
            }
        } else {
            cur->completed = 1; done++;
            cur->turnaround = time - cur->arrival;
            cur->waiting = cur->turnaround - cur->burst;
        }

        it = p;
        while (it) {
            if (it != cur && !it->inqueue && it->arrival <= time && it->remaining > 0) {
                enqueue(L1, it);
                it->inqueue = 1;
            }
            it = it->next;
        }
    }

    printf("\n--- MLFQ Results (tq1=%d, tq2=%d) ---\n", tq1, tq2);
    printResults(p);
    freeList(p);
    freeQ(L1);
    freeQ(L2);
}
              
