#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

// Function to check if the queue is empty
int isEmpty() {
    return (front == -1 || front > rear);
}

// Function to check if the queue is full
int isFull() {
    return (rear == MAX - 1);
}

// Function to add an element to the queue
void enqueue(int value) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = value;
    printf("%d enqueued to queue\n", value);
}

// Function to remove an element from the queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        return;
    }
    printf("%d dequeued from queue\n", queue[front]);
    front++;
}

// Function to get the front element of the queue
void peek() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    printf("Front element: %d\n", queue[front]);
}

// Function to display the queue
void display() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main() 
{
    int choice, value;
    while (1) {
        printf("\n--- Queue Operations ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peek();
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}