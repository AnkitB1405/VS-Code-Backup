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

insert_at_position(struct Node** head, int val, int pos) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val;
    if (pos == 0) {
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
        *head = newnode;
        return;
    }
    struct Node* temp = *head;
    for (int i = 0; i < pos - 1; i++) {
        temp = temp->next;
        if (temp == *head) break; // position is out of bounds
    }
    newnode->next = temp->next;
    newnode->prev = temp;
    temp->next->prev = newnode;
    temp->next = newnode;
}

int main() {
    struct Node* head = NULL;
    int choice, val, pos;
    while (1) {
        printf("1. Insert at end\n2. Insert at position\n3. Delete node\n4. Traverse\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert_end(&head, val);
                break;
            case 2:
                printf("Enter value and position to insert: ");
                scanf("%d %d", &val, &pos);
                insert_at_position(&head, val, pos);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                delete_node(&head, val);
                break;
            case 4:
                traverse(head);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
