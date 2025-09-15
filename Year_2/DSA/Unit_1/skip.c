#include <stdio.h>
#include <stdlib.h>
#define MAXLVL 3
#define P 0.5

typedef struct snode {
    int key;
    struct snode **forward;
} snode;

typedef struct skiplist {
    int level;
    struct snode *header;
} skiplist;

skiplist* createList();
snode* createNode(int, int);
int randomLevel();

int main() {
    skiplist* list = createList();
    // Insert/search etc. functions go here (see next code snippet)
    return 0;
}
// (Functions not shown for brevity; see operations code below)
skiplist* createList() {
    skiplist* list = malloc(sizeof(skiplist));
    list->level = 0;
    list->header = createNode(-1, MAXLVL);
    for (int i = 0; i < MAXLVL; i++)
        list->header->forward[i] = NULL;
    return list;
}
skiplist* createNode(int key, int level) {
    snode* n = malloc(sizeof(snode));
    n->key = key;
    n->forward = malloc(sizeof(snode*) * (level + 1));
    for (int i = 0; i <= level; i++)
        n->forward[i] = NULL;
    return n;
}
/*
 * A skip list is a probabilistic data structure used for storing and retrieving data quickly.
 * It is a linked list where each node has a certain number of levels (up to a maximum of MAXLVL).
 * The level of each node is randomly chosen when the node is inserted into the list.
 * The level of a node determines how many pointers it has to other nodes in the list.
 * The pointers in a node point to the next node in the list at each level.
 * The highest level (MAXLVL) points to the next node in the list, and the lowest level (0) points to the next node in the list.
 * The level of a node is used to determine which node to follow when traversing the list.
 * The higher the level of a node, the more likely it is to be followed.
 * The probability of a node being followed is equal to the probability of a node with the same level being inserted into the list.
 * The probability of a node being inserted into the list is equal to P (0.5 in this case).
 * The probability of a node with level i being inserted into the list is equal to P^i.
 * The probability of a node with level i being followed is equal to P^(i-1).
 */
