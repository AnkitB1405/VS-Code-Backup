#include <stdio.h>
#include <stdlib.h>

struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
};

// Insert at beginning
void insertBeginning(struct DNode** head, int data) {
    struct DNode* newNode = (struct DNode*)malloc(sizeof(struct DNode));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = *head;
    
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Insert at end
void insertEnd(struct DNode** head, int data) {
    struct DNode* newNode = (struct DNode*)malloc(sizeof(struct DNode));
    newNode->data = data;
    newNode->next = NULL;
    
    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }
    
    struct DNode* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
}

// Delete node by position
void deleteAtPosition(struct DNode** head, int position) {
    if (*head == NULL) return;
    
    struct DNode* temp = *head;
    
    if (position == 0) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
        return;
    }
    
    for (int i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) return;
    
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    
    free(temp);
}

// Example 1: Reverse doubly linked list
void reverseDLL(struct DNode** head) {
    struct DNode* temp = NULL;
    struct DNode* current = *head;
    
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    if (temp != NULL) {
        *head = temp->prev;
    }
}

// Example 2: Find pairs with given sum
void findPairs(struct DNode* head, int sum) {
    struct DNode* first = head;
    struct DNode* second = head;
    
    while (second->next != NULL) {
        second = second->next;
    }
    
    while (first != NULL && second != NULL && 
           first != second && second->next != first) {
        
        int pairSum = first->data + second->data;
        
        if (pairSum == sum) {
            printf("Pair: (%d, %d)\n", first->data, second->data);
            first = first->next;
            second = second->prev;
        } else if (pairSum < sum) {
            first = first->next;
        } else {
            second = second->prev;
        }
    }
}