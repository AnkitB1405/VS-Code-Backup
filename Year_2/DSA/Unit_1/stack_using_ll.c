#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** top, int x) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = x; newnode->next = *top;
    *top = newnode;
}

int pop(struct Node** top) {
    if(!*top) return -1;
    struct Node* temp = *top;
    int val = temp->data;
    *top = temp->next;
    free(temp);
    return val;
}

int main() {
    struct Node* stack = NULL;
    push(&stack, 5); push(&stack, 10);
    printf("Pop: %d\n", pop(&stack));
    return 0;
}
