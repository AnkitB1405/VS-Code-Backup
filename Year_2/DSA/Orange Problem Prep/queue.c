#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// Basic Queue
struct Queue {
    int items[SIZE];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(struct Queue* q) {
    return (q->rear == SIZE - 1);
}

int isEmpty(struct Queue* q) {
    return (q->front == -1 || q->front > q->rear);
}

void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front++];
}

// Circular Queue
struct CircularQueue {
    int items[SIZE];
    int front, rear;
};

void initCircularQueue(struct CircularQueue* q) {
    q->front = -1;
    q->rear = -1;
}

int isCircularFull(struct CircularQueue* q) {
    return ((q->rear + 1) % SIZE == q->front);
}

int isCircularEmpty(struct CircularQueue* q) {
    return (q->front == -1);
}

void circularEnqueue(struct CircularQueue* q, int value) {
    if (isCircularFull(q)) {
        printf("Circular queue is full\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear = (q->rear + 1) % SIZE;
    q->items[q->rear] = value;
}

int circularDequeue(struct CircularQueue* q) {
    if (isCircularEmpty(q)) {
        printf("Circular queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }
    return item;
}

// Priority Queue
struct PriorityQueue {
    int items[SIZE];
    int size;
};

void initPriorityQueue(struct PriorityQueue* pq) {
    pq->size = 0;
}

void priorityEnqueue(struct PriorityQueue* pq, int value) {
    if (pq->size == SIZE) {
        printf("Priority queue is full\n");
        return;
    }
    
    int i;
    for (i = pq->size - 1; i >= 0; i--) {
        if (pq->items[i] > value) {
            pq->items[i + 1] = pq->items[i];
        } else {
            break;
        }
    }
    pq->items[i + 1] = value;
    pq->size++;
}

int priorityDequeue(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty\n");
        return -1;
    }
    return pq->items[--pq->size];
}

// Double Ended Queue (Deque)
struct Deque {
    int items[SIZE];
    int front, rear;
};

void initDeque(struct Deque* dq) {
    dq->front = -1;
    dq->rear = 0;
}

int isDequeFull(struct Deque* dq) {
    return ((dq->front == 0 && dq->rear == SIZE - 1) || dq->front == dq->rear + 1);
}

int isDequeEmpty(struct Deque* dq) {
    return (dq->front == -1);
}

void insertFront(struct Deque* dq, int value) {
    if (isDequeFull(dq)) {
        printf("Deque is full\n");
        return;
    }
    
    if (dq->front == -1) {
        dq->front = dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = SIZE - 1;
    } else {
        dq->front--;
    }
    dq->items[dq->front] = value;
}

void insertRear(struct Deque* dq, int value) {
    if (isDequeFull(dq)) {
        printf("Deque is full\n");
        return;
    }
    
    if (dq->front == -1) {
        dq->front = dq->rear = 0;
    } else if (dq->rear == SIZE - 1) {
        dq->rear = 0;
    } else {
        dq->rear++;
    }
    dq->items[dq->rear] = value;
}