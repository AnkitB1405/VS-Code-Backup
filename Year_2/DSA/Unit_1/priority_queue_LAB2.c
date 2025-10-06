#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000  

// ---------------- Athlete Struct ----------------
typedef struct {
    int score;
    int index;
} Athlete;

// ---------------- Priority Queue (Array-based) ----------------
typedef struct {
    Athlete data[MAX_SIZE];
    int size;
} PriorityQueue;


void initPQ(PriorityQueue* pq){
     // Initialize priority queue
}


void pushPQ(PriorityQueue* pq, Athlete athlete){
     // Insert athlete into priority queue in descending order
}

Athlete popPQ(PriorityQueue* pq){
     // Remove max element (largest score)
}

// ---------------- Functions to be implemented ----------------

void getRankString(int rank, char* rankStr){
     // Get rank string based on position
    if (rank == 1) {
        strcpy(rankStr, "Gold Medal");
    } else if (rank == 2) {
        strcpy(rankStr, "Silver Medal");
    } else if (rank == 3) {
        strcpy(rankStr, "Bronze Medal");
    } else {
        sprintf(rankStr, "%d", rank);
    }

}

void findRelativeRanks(int* scores, int scoresSize, char** result){
     // Main function to find relative ranks using priority queue
}

// ---------------- Main Function ----------------
int main() {
    int n;
    scanf("%d", &n);

    int* scores = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    // Allocate memory for result array (array of strings)
    char** result = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        result[i] = (char*)malloc(20 * sizeof(char));
    }

    findRelativeRanks(scores, n, result);

    // Print results
    for (int i = 0; i < n; i++) {
        printf("%s\n", result[i]);
    }

    // Free memory
    for (int i = 0; i < n; i++) free(result[i]);
    free(result);
    free(scores);

    return 0;
}