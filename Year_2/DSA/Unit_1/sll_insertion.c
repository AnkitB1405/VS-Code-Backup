#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert_begin(struct Node** head, int val) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val;
    newnode->next = *head;
    *head = newnode;
}

void insert_at(struct Node** head, int val, int pos) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val;
    if (pos == 0) { // insert at start
        newnode->next = *head;
        *head = newnode;
        return;
    }
    struct Node* temp = *head;
    for (int i = 0; i < pos-1 && temp; i++)
        temp = temp->next;
    if (temp == NULL) return; // position too large
    newnode->next = temp->next;
    temp->next = newnode;
}

void insert_end(struct Node** head, int val) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val; newnode->next = NULL;
    if (!*head) { *head = newnode; return; }
    struct Node* temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newnode;
}

void traverse(struct Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    insert_begin(&head, 10);
    insert_end(&head, 20);
    insert_at(&head, 15, 1);
    traverse(head);
    return 0;
}
