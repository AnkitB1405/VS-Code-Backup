#include <stdio.h>
#include <stdlib.h>
#define MAX 5

int cqueue[MAX];
int front = -1, rear = -1;

// Function to check if the circular queue is empty
int isEmpty()
{
    return (front == -1);
}

// Function to check if the circular queue is full
int isFull()
{
    return ((rear + 1) % MAX == front);
}

// Function to add an element to the circular queue
void enqueue(int value)
{
    if (isFull())
    {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmpty())
    {
        front = rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }
    cqueue[rear] = value;
    printf("%d enqueued to circular queue\n", value);
}

// Function to remove an element from the circular queue
void dequeue()
{
    if (isEmpty())
    {
        printf("Queue Underflow\n");
        return;
    }
    printf("%d dequeued from circular queue\n", cqueue[front]);
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }
}

// Function to get the front element of the circular queue
void peek()
{
    if (isEmpty())
    {
        printf("Circular queue is Empty\n");
        return;
    }
    printf("Front element: %d\n", cqueue[front]);
}

// Function to display the circular queue
void display()
{
    if (isEmpty())
    {
        printf("Circular queue is Empty\n");
        return;
    }
    printf("Circular queue elements: ");
    int i = front;
    while (1)
    {
        printf("%d ", cqueue[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main()
{
    int choice, value;
    while (1)
    {
        printf("\n--- Circular Queue Operations ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
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