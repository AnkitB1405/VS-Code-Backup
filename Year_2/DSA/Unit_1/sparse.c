#include <stdio.h>
#define MAX 10

int main() {
    int mat[MAX][MAX], rows, cols, i, j, count = 0;
    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter elements:\n");
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++) {
            scanf("%d", &mat[i][j]);
            if(mat[i][j] == 0) count++;
        }
    }
    if(count > (rows*cols)/2)
        printf("This is a sparse matrix\n");
    else
        printf("Not a sparse matrix\n");
    return 0;
}
/* A sparse matrix is a matrix in which most of the elements are zero. 
   A common rule of thumb is that a matrix is considered sparse if more than half of its elements are zero. */