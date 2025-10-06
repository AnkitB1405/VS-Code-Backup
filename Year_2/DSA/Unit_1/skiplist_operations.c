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
    int key;
    printf("Enter a key to insert into the skip list: ");
    scanf("%d", &key);
    insert(list, key);
    return 0;
}
// (Functions not shown for brevity; see operations code below)
// Add to the above skip list code

void insert(skiplist *list, int key) {
    snode *update[MAXLVL+1];
    snode *x = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward;

    if (!x || x->key != key) {
        int lvl = randomLevel();
        if (lvl > list->level) {
            for (int i = list->level + 1; i <= lvl; i++)
                update[i] = list->header;
            list->level = lvl;
        }
        x = createNode(key, lvl);
        for (int i = 0; i <= lvl; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
}
int randomLevel() {
    int lvl = 0;
    while ((rand() / (double)RAND_MAX) < P && lvl < MAXLVL)
        lvl++;
    return lvl;
}
snode* createNode(int key, int level) {
    snode* n = malloc(sizeof(snode));
    n->key = key;
    n->forward = malloc(sizeof(snode*) * (level + 1));
    for (int i = 0; i <= level; i++)
        n->forward[i] = NULL;
    return n;
}
/*
skiplist* search(skiplist *list, int key) {
    snode *x = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
    }
    x = x->forward[0];
    if (x && x->key == key)
        return x;
    return NULL;
}
*/