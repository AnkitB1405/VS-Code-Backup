#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert_end(struct Node** tail, int val) {
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val;
    if (*tail == NULL) {
        newnode->next = newnode;
        *tail = newnode;
    } else {
        newnode->next = (*tail)->next;
        (*tail)->next = newnode;
        *tail = newnode;
    }
}

void traverse(struct Node* tail) {
    if(!tail) { printf("Empty\n"); return;}
    struct Node *p = tail->next;
    do {
        printf("%d -> ", p->data);
        p = p->next;
    } while (p != tail->next);
    printf("\n");
}

void delete_node(struct Node** tail, int key) {
    if (!*tail) return;
    struct Node *curr = (*tail)->next, *prev = *tail;
    do {
        if (curr->data == key) {
            if (curr == prev) { // only one node
                free(curr);
                *tail = NULL;
            } else {
                prev->next = curr->next;
                if (curr == *tail) *tail = prev; // update tail if needed
                free(curr);
            }
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != (*tail)->next);
}

void insert_at_position(struct Node** tail, int val, int pos) {
    if (pos < 1) {
        printf("Position should be >= 1\n");
        return;
    }
    struct Node* newnode = malloc(sizeof(struct Node));
    newnode->data = val;
    if (*tail == NULL) {
        if (pos != 1) {
            printf("List is empty. Can only insert at position 1.\n");
            free(newnode);
            return;
        }
        newnode->next = newnode;
        *tail = newnode;
    } else if (pos == 1) {
        newnode->next = (*tail)->next;
        (*tail)->next = newnode;
    } else {
        struct Node* curr = (*tail)->next;
        for (int i = 1; i < pos - 1; i++) {
            curr = curr->next;
            if (curr == (*tail)->next) {
                printf("Position out of bounds. Inserting at end.\n");
                break;
            }
        }
        newnode->next = curr->next;
        curr->next = newnode;
        if (curr == *tail) *tail = newnode; // update tail if inserted at end
    }
}
int main() {
    struct Node* tail = NULL;
    int choice, val, key;
    while (1) {
        printf("\n--- Circular Singly Linked List Operations ---\n");
        printf("1. Insert at end\n");
        printf("2. Insert at position\n");
        printf("3. Delete node\n");
        printf("4. Traverse\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert_end(&tail, val);
                break;
            case 2:
                printf("Enter value and position to insert: ");
                scanf("%d %d", &val, &key);
                insert_at_position(&tail, val, key);
                break;
            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &key);
                delete_node(&tail, key);
                break;
            case 4:
                traverse(tail);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}