#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Circular Linked List
struct CNode {
    int data;
    struct CNode* next;
};

void insertCircular(struct CNode** head, int data) {
    struct CNode* newNode = (struct CNode*)malloc(sizeof(struct CNode));
    newNode->data = data;
    
    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
        return;
    }
    
    struct CNode* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->next = *head;
}

// Skip List Implementation
#define MAX_LEVEL 6

struct SkipNode {
    int value;
    struct SkipNode** forward;
};

struct SkipList {
    int level;
    struct SkipNode* header;
};

struct SkipNode* createNode(int level, int value) {
    struct SkipNode* newNode = (struct SkipNode*)malloc(sizeof(struct SkipNode));
    newNode->value = value;
    newNode->forward = (struct SkipNode**)malloc(sizeof(struct SkipNode*) * (level + 1));
    for (int i = 0; i <= level; i++) {
        newNode->forward[i] = NULL;
    }
    return newNode;
}

struct SkipList* createSkipList() {
    struct SkipList* list = (struct SkipList*)malloc(sizeof(struct SkipList));
    list->level = 0;
    list->header = createNode(MAX_LEVEL, -1);
    return list;
}

int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

void skipInsert(struct SkipList* list, int value) {
    struct SkipNode* update[MAX_LEVEL + 1];
    struct SkipNode* current = list->header;
    
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (current == NULL || current->value != value) {
        int newLevel = randomLevel();
        
        if (newLevel > list->level) {
            for (int i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }
        
        struct SkipNode* newNode = createNode(newLevel, value);
        
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// ...existing code...

// Circular Doubly Linked List
struct CDNode {
    int data;
    struct CDNode* next;
    struct CDNode* prev;
};

void insertCDL(struct CDNode** head, int data) {
    struct CDNode* newNode = (struct CDNode*)malloc(sizeof(struct CDNode));
    newNode->data = data;
    if (*head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
        return;
    }
    struct CDNode* tail = (*head)->prev;
    newNode->next = *head;
    newNode->prev = tail;
    tail->next = newNode;
    (*head)->prev = newNode;
}

void printCDL(struct CDNode* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct CDNode* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// ...existing code...