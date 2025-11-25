/*
 * BINARY SEARCH TREE - APPLICATIONS
 * ==================================
 * 
 * This file demonstrates practical applications of BST:
 * 1. Checking if a tree is a valid BST
 * 2. Finding kth smallest/largest element
 * 3. Range queries (find all elements in a range)
 * 4. Lowest Common Ancestor (LCA)
 * 5. Converting sorted array to BST
 * 6. Finding floor and ceiling values
 * 7. Checking if two BSTs are identical
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Basic insert function (from basic operations)
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

/*
 * APPLICATION 1: CHECK IF A TREE IS A VALID BST
 * ---------------------------------------------
 * A valid BST must satisfy:
 * - All nodes in left subtree < current node
 * - All nodes in right subtree > current node
 * 
 * We use min and max bounds to check this
 */
int isBSTUtil(struct Node* root, int min, int max) {
    // Empty tree is a BST
    if (root == NULL) {
        return 1;
    }
    
    // Check if current node violates BST property
    if (root->data <= min || root->data >= max) {
        return 0;  // Not a valid BST
    }
    
    // Check left subtree (all values must be < root->data)
    // Check right subtree (all values must be > root->data)
    return isBSTUtil(root->left, min, root->data) && 
           isBSTUtil(root->right, root->data, max);
}

int isBST(struct Node* root) {
    // Use INT_MIN and INT_MAX as initial bounds
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

/*
 * APPLICATION 2: FIND Kth SMALLEST ELEMENT
 * ----------------------------------------
 * Since inorder traversal gives sorted order,
 * the kth element in inorder is the kth smallest
 * 
 * Example: For BST [50, 30, 70, 20, 40, 60, 80]
 * Inorder: 20, 30, 40, 50, 60, 70, 80
 * 3rd smallest = 40
 */
void kthSmallestUtil(struct Node* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k) {
        return;
    }
    
    // Inorder traversal: Left -> Root -> Right
    kthSmallestUtil(root->left, k, count, result);
    
    // Increment count when we visit a node
    (*count)++;
    
    // If this is the kth node, store the result
    if (*count == k) {
        *result = root->data;
        return;
    }
    
    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(struct Node* root, int k) {
    int count = 0;
    int result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}

/*
 * APPLICATION 3: FIND Kth LARGEST ELEMENT
 * ---------------------------------------
 * Reverse inorder traversal: Right -> Root -> Left
 * This gives elements in descending order
 */
void kthLargestUtil(struct Node* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k) {
        return;
    }
    
    // Reverse inorder: Right -> Root -> Left
    kthLargestUtil(root->right, k, count, result);
    
    (*count)++;
    
    if (*count == k) {
        *result = root->data;
        return;
    }
    
    kthLargestUtil(root->left, k, count, result);
}

int kthLargest(struct Node* root, int k) {
    int count = 0;
    int result = -1;
    kthLargestUtil(root, k, &count, &result);
    return result;
}

/*
 * APPLICATION 4: RANGE QUERY
 * --------------------------
 * Print all elements in BST that fall within range [low, high]
 * 
 * Example: For BST [50, 30, 70, 20, 40, 60, 80]
 * Range [25, 65] would print: 30, 40, 50, 60
 */
void rangeQuery(struct Node* root, int low, int high) {
    if (root == NULL) {
        return;
    }
    
    // If current node is greater than low, there might be nodes in left subtree
    if (root->data > low) {
        rangeQuery(root->left, low, high);
    }
    
    // If current node is in range, print it
    if (root->data >= low && root->data <= high) {
        printf("%d ", root->data);
    }
    
    // If current node is less than high, there might be nodes in right subtree
    if (root->data < high) {
        rangeQuery(root->right, low, high);
    }
}

/*
 * APPLICATION 5: LOWEST COMMON ANCESTOR (LCA)
 * -------------------------------------------
 * LCA of two nodes is the deepest node that is ancestor of both
 * 
 * BST Property helps us:
 * - If both nodes are smaller than current, LCA is in left subtree
 * - If both nodes are larger than current, LCA is in right subtree
 * - Otherwise, current node is the LCA
 * 
 * Example: For BST [50, 30, 70, 20, 40, 60, 80]
 * LCA(20, 40) = 30
 * LCA(20, 80) = 50
 */
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL) {
        return NULL;
    }
    
    // If both n1 and n2 are smaller than root, LCA is in left subtree
    if (n1 < root->data && n2 < root->data) {
        return findLCA(root->left, n1, n2);
    }
    
    // If both n1 and n2 are larger than root, LCA is in right subtree
    if (n1 > root->data && n2 > root->data) {
        return findLCA(root->right, n1, n2);
    }
    
    // If one is on left and one is on right (or one equals root), root is LCA
    return root;
}

/*
 * APPLICATION 6: CONVERT SORTED ARRAY TO BALANCED BST
 * ---------------------------------------------------
 * Given a sorted array, create a height-balanced BST
 * 
 * Strategy: Take middle element as root
 * - Left half becomes left subtree
 * - Right half becomes right subtree
 * 
 * This ensures the tree is balanced (minimum height)
 */
struct Node* sortedArrayToBST(int arr[], int start, int end) {
    // Base case
    if (start > end) {
        return NULL;
    }
    
    // Find middle element
    int mid = start + (end - start) / 2;
    
    // Make middle element the root
    struct Node* root = createNode(arr[mid]);
    
    // Recursively construct left subtree from left half
    root->left = sortedArrayToBST(arr, start, mid - 1);
    
    // Recursively construct right subtree from right half
    root->right = sortedArrayToBST(arr, mid + 1, end);
    
    return root;
}

/*
 * APPLICATION 7: FIND FLOOR VALUE
 * -------------------------------
 * Floor of a value x = largest value in BST that is <= x
 * 
 * Example: For BST [50, 30, 70, 20, 40, 60, 80]
 * Floor(55) = 50
 * Floor(35) = 30
 * Floor(90) = 80
 */
int findFloor(struct Node* root, int x) {
    int floor = -1;  // Initialize to -1 (not found)
    
    while (root != NULL) {
        // If we found exact match
        if (root->data == x) {
            return root->data;
        }
        
        // If current node is less than x, it could be floor
        // But there might be a larger value in right subtree
        if (root->data < x) {
            floor = root->data;
            root = root->right;  // Look for larger value
        }
        // If current node is greater than x, floor must be in left subtree
        else {
            root = root->left;
        }
    }
    
    return floor;
}

/*
 * APPLICATION 8: FIND CEILING VALUE
 * ---------------------------------
 * Ceiling of a value x = smallest value in BST that is >= x
 * 
 * Example: For BST [50, 30, 70, 20, 40, 60, 80]
 * Ceiling(55) = 60
 * Ceiling(35) = 40
 * Ceiling(15) = 20
 */
int findCeiling(struct Node* root, int x) {
    int ceiling = -1;  // Initialize to -1 (not found)
    
    while (root != NULL) {
        // If we found exact match
        if (root->data == x) {
            return root->data;
        }
        
        // If current node is greater than x, it could be ceiling
        // But there might be a smaller value in left subtree
        if (root->data > x) {
            ceiling = root->data;
            root = root->left;  // Look for smaller value
        }
        // If current node is less than x, ceiling must be in right subtree
        else {
            root = root->right;
        }
    }
    
    return ceiling;
}

/*
 * APPLICATION 9: CHECK IF TWO BSTs ARE IDENTICAL
 * ----------------------------------------------
 * Two trees are identical if:
 * - Both are empty, OR
 * - Both have same data at root, and
 * - Left subtrees are identical, and
 * - Right subtrees are identical
 */
int areIdentical(struct Node* root1, struct Node* root2) {
    // Both empty
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }
    
    // One empty, one not
    if (root1 == NULL || root2 == NULL) {
        return 0;
    }
    
    // Check current nodes and recursively check subtrees
    return (root1->data == root2->data) &&
           areIdentical(root1->left, root2->left) &&
           areIdentical(root1->right, root2->right);
}

/*
 * APPLICATION 10: COUNT NODES IN A GIVEN RANGE
 * --------------------------------------------
 * Count how many nodes have values in range [low, high]
 */
int countInRange(struct Node* root, int low, int high) {
    if (root == NULL) {
        return 0;
    }
    
    int count = 0;
    
    // If current node is in range, count it
    if (root->data >= low && root->data <= high) {
        count = 1;
    }
    
    // Recursively count in left and right subtrees
    if (root->data > low) {
        count += countInRange(root->left, low, high);
    }
    
    if (root->data < high) {
        count += countInRange(root->right, low, high);
    }
    
    return count;
}

// Helper function for display
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/*
 * MAIN FUNCTION - DEMONSTRATES ALL APPLICATIONS
 * ---------------------------------------------
 */
int main() {
    struct Node* root = NULL;
    
    printf("=== BINARY SEARCH TREE APPLICATIONS ===\n\n");
    
    // Create a BST
    printf("Creating BST with values: 50, 30, 70, 20, 40, 60, 80\n");
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n\n");
    
    // Application 1: Check if valid BST
    printf("1. Is this a valid BST? %s\n", isBST(root) ? "Yes" : "No");
    
    // Application 2 & 3: Kth smallest and largest
    printf("\n2. 3rd smallest element: %d", kthSmallest(root, 3));
    printf("\n3. 3rd largest element: %d", kthLargest(root, 3));
    
    // Application 4: Range query
    printf("\n\n4. Elements in range [25, 65]: ");
    rangeQuery(root, 25, 65);
    
    // Application 5: LCA
    printf("\n\n5. LCA of 20 and 40: %d", findLCA(root, 20, 40)->data);
    printf("\n   LCA of 20 and 80: %d", findLCA(root, 20, 80)->data);
    
    // Application 6: Sorted array to BST
    printf("\n\n6. Converting sorted array [10, 20, 30, 40, 50] to BST:");
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* balancedTree = sortedArrayToBST(arr, 0, n - 1);
    printf("\n   Inorder of new tree: ");
    inorder(balancedTree);
    
    // Application 7 & 8: Floor and Ceiling
    printf("\n\n7. Floor of 55: %d", findFloor(root, 55));
    printf("\n   Floor of 35: %d", findFloor(root, 35));
    printf("\n\n8. Ceiling of 55: %d", findCeiling(root, 55));
    printf("\n   Ceiling of 35: %d", findCeiling(root, 35));
    
    // Application 9: Check if identical
    struct Node* root2 = NULL;
    root2 = insert(root2, 50);
    root2 = insert(root2, 30);
    root2 = insert(root2, 70);
    printf("\n\n9. Are original tree and partial copy identical? %s", 
           areIdentical(root, root2) ? "Yes" : "No");
    
    // Application 10: Count in range
    printf("\n\n10. Count of nodes in range [25, 65]: %d", 
           countInRange(root, 25, 65));
    
    printf("\n\n");
    return 0;
}
