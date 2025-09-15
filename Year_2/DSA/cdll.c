#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void insert_end(struct Node** head, int val) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val;
    if (!(*head)) {
        newnode->next = newnode->prev = newnode;
        *head = newnode;
        return;
    }
    struct Node* last = (*head)->prev;
    newnode->next = *head;
    (*head)->prev = newnode;
    newnode->prev = last;
    last->next = newnode;
}

void traverse(struct Node* head) {
    if(!head) return;
    struct Node* temp = head;
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while(temp != head);
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    insert_end(&head, 10); insert_end(&head, 20); insert_end(&head, 30);
    traverse(head);
    return 0;
}
void delete_node(struct Node** head, int key) {
    if (!*head) return;
    struct Node *curr = *head, *prev = NULL;
    do {
        if (curr->data == key) {
            if (curr->next == curr) { // only one node
                free(curr);
                *head = NULL;
            } else {
                if (prev) prev->next = curr->next;
                curr->next->prev = curr->prev;
                if (curr == *head) *head = curr->next; // update head if needed
                free(curr);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != *head);
}