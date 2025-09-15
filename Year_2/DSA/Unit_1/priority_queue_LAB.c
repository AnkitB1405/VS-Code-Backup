#include <stdio.h>

// Insert value in priority queue
void insertPQ(int pq[], int *size, int value) {
   //implement insertPq function
}

// Delete the maximum (first element)
int deleteMaxPQ(int pq[], int *size) {
    //implement deleteMaxPQ function
}

int lastStoneWeight(int* stones, int stonesSize) {
    int pq[100];
    int size = 0;

    // Insert all stones into priority queue
    for (int i = 0; i < stonesSize; i++) {
        insertPQ(pq, &size, stones[i]);
    }

    // Implement code to find the last Stone weight here.
    
}

int main() {
    int n;
    scanf("%d", &n);

    int stones[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &stones[i]);
    }

    int result = lastStoneWeight(stones, n);
    printf("%d\n", result);

    return 0;
}