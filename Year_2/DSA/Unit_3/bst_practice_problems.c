/*
 * BST PRACTICE PROBLEMS AND SOLUTIONS
 * ===================================
 * 
 * This file contains common BST problems asked in exams and interviews
 * Each problem has detailed explanation and solution
 * 
 * Problems covered:
 * 1. Find height/depth of BST
 * 2. Check if tree is balanced
 * 3. Mirror/Invert a BST
 * 4. Find diameter of tree
 * 5. Print all paths from root to leaf
 * 6. Convert BST to Greater Sum Tree
 * 7. Find distance between two nodes
 * 8. Check if two trees are identical
 * 9. Serialize and Deserialize BST
 * 10. Find kth smallest without extra space
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

// Create new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Basic insert
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->data) root->left = insert(root->left, value);
    else if (value > root->data) root->right = insert(root->right, value);
    return root;
}

/*
 * PROBLEM 1: FIND HEIGHT OF BST
 * -----------------------------
 * Height = longest path from root to leaf (in edges)
 * 
 * Approach: Recursively find height of left and right subtrees
 * Height = 1 + max(left height, right height)
 */
int findHeight(struct Node* root) {
    // Base case: empty tree has height -1
    if (root == NULL) {
        return -1;
    }
    
    // Recursive case
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

/*
 * PROBLEM 2: CHECK IF TREE IS BALANCED
 * ------------------------------------
 * A tree is balanced if for every node:
 * |height(left) - height(right)| <= 1
 * 
 * Approach: Check balance at each node recursively
 */
int isBalanced(struct Node* root) {
    if (root == NULL) {
        return 1;  // Empty tree is balanced
    }
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    // Check if current node is balanced
    if (abs(leftHeight - rightHeight) > 1) {
        return 0;  // Not balanced
    }
    
    // Recursively check if left and right subtrees are balanced
    return isBalanced(root->left) && isBalanced(root->right);
}

/*
 * PROBLEM 3: MIRROR/INVERT A BST
 * ------------------------------
 * Convert tree to its mirror image (swap left and right children)
 * 
 * Example:
 *     4              4
 *    / \            / \
 *   2   6    =>    6   2
 *  / \            / \
 * 1   3          3   1
 */
struct Node* mirrorTree(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }
    
    // Swap left and right children
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    // Recursively mirror left and right subtrees
    mirrorTree(root->left);
    mirrorTree(root->right);
    
    return root;
}

/*
 * PROBLEM 4: FIND DIAMETER OF TREE
 * --------------------------------
 * Diameter = longest path between any two nodes
 * (Path may or may not pass through root)
 * 
 * Approach: For each node, diameter is either:
 * 1. Diameter of left subtree, OR
 * 2. Diameter of right subtree, OR
 * 3. Longest path through root (left height + right height + 2)
 */
int findDiameter(struct Node* root, int* maxDiameter) {
    if (root == NULL) {
        return -1;
    }
    
    // Get heights of left and right subtrees
    int leftHeight = findDiameter(root->left, maxDiameter);
    int rightHeight = findDiameter(root->right, maxDiameter);
    
    // Update diameter if path through current node is longer
    int currentDiameter = leftHeight + rightHeight + 2;
    if (currentDiameter > *maxDiameter) {
        *maxDiameter = currentDiameter;
    }
    
    // Return height of current node
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int diameter(struct Node* root) {
    int maxDiameter = 0;
    findDiameter(root, &maxDiameter);
    return maxDiameter;
}

/*
 * PROBLEM 5: PRINT ALL ROOT-TO-LEAF PATHS
 * ---------------------------------------
 * Print all paths from root to leaves
 * 
 * Approach: Use an array to store current path
 * When we reach a leaf, print the path
 */
void printPathsUtil(struct Node* root, int path[], int pathLen) {
    if (root == NULL) {
        return;
    }
    
    // Add current node to path
    path[pathLen] = root->data;
    pathLen++;
    
    // If leaf node, print the path
    if (root->left == NULL && root->right == NULL) {
        printf("Path: ");
        for (int i = 0; i < pathLen; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    }
    else {
        // Recursively print paths in left and right subtrees
        printPathsUtil(root->left, path, pathLen);
        printPathsUtil(root->right, path, pathLen);
    }
}

void printAllPaths(struct Node* root) {
    int path[1000];  // Assuming max depth is 1000
    printPathsUtil(root, path, 0);
}

/*
 * PROBLEM 6: CONVERT BST TO GREATER SUM TREE
 * ------------------------------------------
 * Replace each node's value with sum of all greater values
 * 
 * Example:
 *     4              13
 *    / \            /  \
 *   2   6    =>    15   6
 *  / \            /  \
 * 1   3          16  13
 * 
 * Approach: Reverse inorder traversal (Right -> Root -> Left)
 * Keep running sum and update each node
 */
void convertToGSTUtil(struct Node* root, int* sum) {
    if (root == NULL) {
        return;
    }
    
    // Reverse inorder: Right -> Root -> Left
    convertToGSTUtil(root->right, sum);
    
    // Update current node
    *sum += root->data;
    root->data = *sum;
    
    convertToGSTUtil(root->left, sum);
}

void convertToGreaterSumTree(struct Node* root) {
    int sum = 0;
    convertToGSTUtil(root, &sum);
}

/*
 * PROBLEM 7: FIND DISTANCE BETWEEN TWO NODES
 * ------------------------------------------
 * Distance = number of edges between two nodes
 * 
 * Approach:
 * 1. Find Lowest Common Ancestor (LCA)
 * 2. Distance = distance(LCA to node1) + distance(LCA to node2)
 */
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;
    
    if (n1 < root->data && n2 < root->data) {
        return findLCA(root->left, n1, n2);
    }
    
    if (n1 > root->data && n2 > root->data) {
        return findLCA(root->right, n1, n2);
    }
    
    return root;
}

int findLevel(struct Node* root, int value, int level) {
    if (root == NULL) return -1;
    
    if (root->data == value) return level;
    
    if (value < root->data) {
        return findLevel(root->left, value, level + 1);
    }
    else {
        return findLevel(root->right, value, level + 1);
    }
}

int findDistance(struct Node* root, int n1, int n2) {
    struct Node* lca = findLCA(root, n1, n2);
    
    if (lca == NULL) return -1;
    
    int dist1 = findLevel(lca, n1, 0);
    int dist2 = findLevel(lca, n2, 0);
    
    return dist1 + dist2;
}

/*
 * PROBLEM 8: CHECK IF TWO TREES ARE IDENTICAL
 * -------------------------------------------
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
    
    // Check data and recursively check subtrees
    return (root1->data == root2->data) &&
           areIdentical(root1->left, root2->left) &&
           areIdentical(root1->right, root2->right);
}

/*
 * PROBLEM 9: COUNT LEAF NODES
 * ---------------------------
 */
int countLeaves(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    // If leaf node
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    
    // Count leaves in left and right subtrees
    return countLeaves(root->left) + countLeaves(root->right);
}

/*
 * PROBLEM 10: SUM OF ALL NODES
 * ----------------------------
 */
int sumOfNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    return root->data + sumOfNodes(root->left) + sumOfNodes(root->right);
}

/*
 * PROBLEM 11: PRINT LEVEL ORDER TRAVERSAL
 * ---------------------------------------
 * Print nodes level by level
 * 
 * Approach: Use queue (here we use simple array-based queue)
 */
void levelOrder(struct Node* root) {
    if (root == NULL) return;
    
    // Simple array-based queue
    struct Node* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);
        
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

/*
 * PROBLEM 12: FIND MAXIMUM VALUE IN BST
 * -------------------------------------
 * (Without using the fact that it's a BST)
 */
int findMax(struct Node* root) {
    if (root == NULL) {
        return INT_MIN;
    }
    
    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);
    
    int maxValue = root->data;
    if (leftMax > maxValue) maxValue = leftMax;
    if (rightMax > maxValue) maxValue = rightMax;
    
    return maxValue;
}

// Helper for display
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/*
 * MAIN FUNCTION - DEMONSTRATES ALL PROBLEMS
 * -----------------------------------------
 */
int main() {
    struct Node* root = NULL;
    
    printf("=== BST PRACTICE PROBLEMS ===\n\n");
    
    // Create a BST
    printf("Creating BST: 50, 30, 70, 20, 40, 60, 80\n");
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printf("Inorder: ");
    inorder(root);
    printf("\n\n");
    
    // Problem 1: Height
    printf("1. Height of tree: %d\n", findHeight(root));
    
    // Problem 2: Balanced
    printf("2. Is tree balanced? %s\n", isBalanced(root) ? "Yes" : "No");
    
    // Problem 3: Mirror
    printf("3. Mirroring the tree...\n");
    mirrorTree(root);
    printf("   Inorder after mirror: ");
    inorder(root);
    mirrorTree(root);  // Mirror back to original
    printf("\n");
    
    // Problem 4: Diameter
    printf("4. Diameter of tree: %d\n", diameter(root));
    
    // Problem 5: All paths
    printf("5. All root-to-leaf paths:\n");
    printAllPaths(root);
    
    // Problem 6: Greater Sum Tree
    printf("\n6. Converting to Greater Sum Tree...\n");
    struct Node* gstRoot = NULL;
    gstRoot = insert(gstRoot, 4);
    gstRoot = insert(gstRoot, 2);
    gstRoot = insert(gstRoot, 6);
    gstRoot = insert(gstRoot, 1);
    gstRoot = insert(gstRoot, 3);
    printf("   Before: ");
    inorder(gstRoot);
    convertToGreaterSumTree(gstRoot);
    printf("\n   After:  ");
    inorder(gstRoot);
    
    // Problem 7: Distance
    printf("\n\n7. Distance between 20 and 40: %d\n", findDistance(root, 20, 40));
    printf("   Distance between 20 and 80: %d\n", findDistance(root, 20, 80));
    
    // Problem 8: Identical
    struct Node* root2 = NULL;
    root2 = insert(root2, 50);
    root2 = insert(root2, 30);
    printf("8. Are trees identical? %s\n", areIdentical(root, root2) ? "Yes" : "No");
    
    // Problem 9: Leaf count
    printf("9. Number of leaf nodes: %d\n", countLeaves(root));
    
    // Problem 10: Sum
    printf("10. Sum of all nodes: %d\n", sumOfNodes(root));
    
    // Problem 11: Level order
    printf("11. Level order traversal: ");
    levelOrder(root);
    
    // Problem 12: Max value
    printf("\n12. Maximum value: %d\n", findMax(root));
    
    printf("\n");
    return 0;
}
