#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
// Josephus Problem using Circular Linked List
int josephus(int n, int k) {
    if (n == 1) return 0;
    return (josephus(n - 1, k) + k) % n;
}

struct Queue {
    int items[SIZE];
    int front, rear;
};


// Josephus using iterative approach
int josephusIterative(int n, int k) {
    int result = 0;
    for (int i = 2; i <= n; i++) {
        result = (result + k) % i;
    }
    return result + 1; // Adding 1 to get 1-based position
}

// CPU Scheduling using Queue (Round Robin)
struct Process {
    int pid;
    int burst_time;
    int remaining_time;
};

void roundRobinScheduling(struct Process processes[], int n, int quantum) {
    struct Queue queue;
    initQueue(&queue);
    
    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        enqueue(&queue, i);
    }
    
    printf("Round Robin Scheduling:\n");
    printf("Time\tProcess\n");
    
    int currentTime = 0;
    while (!isEmpty(&queue)) {
        int idx = dequeue(&queue);
        
        if (processes[idx].remaining_time > quantum) {
            printf("%d-%d\tP%d\n", currentTime, currentTime + quantum, processes[idx].pid);
            currentTime += quantum;
            processes[idx].remaining_time -= quantum;
            enqueue(&queue, idx);
        } else {
            printf("%d-%d\tP%d\n", currentTime, currentTime + processes[idx].remaining_time, processes[idx].pid);
            currentTime += processes[idx].remaining_time;
            processes[idx].remaining_time = 0;
            printf("Process P%d completed at time %d\n", processes[idx].pid, currentTime);
        }
    }
}

// FCFS Scheduling
void fcfsScheduling(struct Process processes[], int n) {
    int completionTime = 0;
    printf("FCFS Scheduling:\n");
    
    for (int i = 0; i < n; i++) {
        completionTime += processes[i].burst_time;
        printf("Process P%d: Arrival: 0, Burst: %d, Completion: %d, Turnaround: %d, Waiting: %d\n",
               processes[i].pid, processes[i].burst_time, completionTime,
               completionTime, completionTime - processes[i].burst_time);
    }
}