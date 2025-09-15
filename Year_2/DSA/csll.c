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

int main() {
    struct Node* tail = NULL;
    insert_end(&tail, 1); insert_end(&tail, 2); insert_end(&tail, 3);
    traverse(tail);
    return 0;
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