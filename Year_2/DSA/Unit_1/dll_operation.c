#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

void insert_front(struct Node** head, int val) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val;
    newnode->prev = NULL; 
    newnode->next = *head;
    if (*head) (*head)->prev = newnode;
    *head = newnode;
}

void insert_end(struct Node** head, int val) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val; 
    newnode->next = NULL;
    if(!*head) { 
        newnode->prev = NULL; 
        *head = newnode; 
        return; }
    struct Node* temp = *head;
    while(temp->next) temp = temp->next;
    temp->next = newnode; 
    newnode->prev = temp;
}

void delete_value(struct Node** head, int val) {
    struct Node* temp = *head;
    while(temp && temp->data != val) temp = temp->next;
    if(!temp) return;
    if(temp->prev) temp->prev->next = temp->next;
    else *head = temp->next;
    if(temp->next) temp->next->prev = temp->prev;
    free(temp);
}

void traverse(struct Node* head) {
    while (head) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    insert_front(&head, 1);
    insert_end(&head, 2);
    insert_end(&head, 3);
    traverse(head);
    delete_value(&head, 2);
    traverse(head);
    return 0;
}