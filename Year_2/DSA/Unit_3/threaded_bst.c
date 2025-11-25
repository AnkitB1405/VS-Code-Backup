/*
 * THREADED BINARY SEARCH TREE
 * ============================
 * 
 * What is a Threaded BST?
 * In a normal BST, many pointers are NULL (wasted space).
 * A threaded BST uses these NULL pointers to store "threads" that point to
 * the inorder predecessor or successor.
 * 
 * Why Threaded BST?
 * 1. Faster inorder traversal (no recursion or stack needed!)
 * 2. Better space utilization
 * 3. Easy to find inorder successor/predecessor
 * 
 * Types of Threading:
 * 1. Single Threaded: Only right NULL pointers are threaded (to successor)
 * 2. Double Threaded: Both left and right NULL pointers are threaded
 * 
 * This file implements SINGLE THREADED BST (right threading)
 * 
 * Example:
 *         20
 *        /  \
 *      10    30
 *       \   /  \
 *       15 25  40
 * 
 * Threaded version (right threads shown with -->):
 *         20
 *        /  \
 *      10    30
 *       \   /  \
 *       15 25  40
 *        |  |   |
 *        v  v   v
 *       20 30  NULL
 * 
 * Node 15's right pointer points to its inorder successor (20)
 * Node 25's right pointer points to its inorder successor (30)
 */

#include <stdio.h>
#include <stdlib.h>

// Node structure for threaded BST
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded;  // 1 if right pointer is a thread, 0 if it's a normal child
};

/*
 * CREATE A NEW NODE
 * ----------------
 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 1;  // Initially, right pointer will be a thread
    return newNode;
}

/*
 * FIND INORDER SUCCESSOR
 * ----------------------
 * In a threaded BST, finding successor is very efficient!
 * 
 * Two cases:
 * 1. If right pointer is a thread, it directly points to successor
 * 2. If right pointer is a child, successor is leftmost node in right subtree
 */
struct Node* inorderSuccessor(struct Node* node) {
    // Case 1: If right is threaded, it points to successor
    if (node->isThreaded) {
        return node->right;
    }
    
    // Case 2: If right is a child, go to right then keep going left
    node = node->right;
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    
    return node;
}

/*
 * INSERT A VALUE INTO THREADED BST
 * ---------------------------------
 * More complex than normal BST because we need to maintain threads
 */
struct Node* insert(struct Node* root, int value) {
    // Case 1: Empty tree
    if (root == NULL) {
        return createNode(value);
    }
    
    struct Node* parent = NULL;
    struct Node* current = root;
    
    // Find the position to insert
    while (current != NULL) {
        parent = current;
        
        if (value < current->data) {
            // Go left
            current = current->left;
        }
        else if (value > current->data) {
            // Go right (but only if it's not a thread)
            if (current->isThreaded) {
                current = NULL;  // Right is a thread, stop here
            }
            else {
                current = current->right;
            }
        }
        else {
            // Duplicate value, don't insert
            return root;
        }
    }
    
    // Create new node
    struct Node* newNode = createNode(value);
    
    // Insert as left or right child of parent
    if (value < parent->data) {
        // Insert as left child
        newNode->right = parent;  // Thread points to parent (inorder successor)
        newNode->isThreaded = 1;
        parent->left = newNode;
    }
    else {
        // Insert as right child
        newNode->right = parent->right;  // Inherit parent's thread
        newNode->isThreaded = parent->isThreaded;
        parent->right = newNode;
        parent->isThreaded = 0;  // Parent's right is now a child, not a thread
    }
    
    return root;
}

/*
 * INORDER TRAVERSAL (WITHOUT RECURSION!)
 * --------------------------------------
 * This is the main advantage of threaded BST
 * We can traverse without recursion or stack!
 */
void inorder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    
    // Find the leftmost node (first node in inorder)
    struct Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    
    // Traverse using threads
    while (current != NULL) {
        printf("%d ", current->data);
        current = inorderSuccessor(current);
    }
}

/*
 * SEARCH FOR A VALUE
 * ------------------
 * Same as normal BST
 */
int search(struct Node* root, int value) {
    struct Node* current = root;
    
    while (current != NULL) {
        if (value == current->data) {
            return 1;  // Found
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            // Only follow right if it's not a thread
            if (current->isThreaded) {
                break;  // Right is a thread, value not found
            }
            current = current->right;
        }
    }
    
    return 0;  // Not found
}

/*
 * FIND MINIMUM VALUE
 * ------------------
 * Leftmost node
 */
struct Node* findMin(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root->left != NULL) {
        root = root->left;
    }
    
    return root;
}

/*
 * FIND MAXIMUM VALUE
 * ------------------
 * Rightmost node (follow right only if not threaded)
 */
struct Node* findMax(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root->right != NULL && !root->isThreaded) {
        root = root->right;
    }
    
    return root;
}

/*
 * PREORDER TRAVERSAL (WITHOUT RECURSION)
 * --------------------------------------
 * Using threaded BST properties
 */
void preorder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    
    struct Node* current = root;
    
    while (current != NULL) {
        printf("%d ", current->data);
        
        // If left child exists, go left
        if (current->left != NULL) {
            current = current->left;
        }
        // Otherwise, follow the thread or right child
        else if (!current->isThreaded) {
            current = current->right;
        }
        else {
            // Follow thread and find next node to visit
            current = current->right;
            while (current != NULL && current->left == NULL && current->isThreaded) {
                current = current->right;
            }
            if (current != NULL && current->left == NULL) {
                current = current->right;
            }
        }
    }
}

/*
 * COUNT TOTAL NODES
 * ----------------
 */
int countNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    int count = 0;
    struct Node* current = root;
    
    // Find leftmost node
    while (current->left != NULL) {
        current = current->left;
    }
    
    // Count using inorder traversal
    while (current != NULL) {
        count++;
        current = inorderSuccessor(current);
    }
    
    return count;
}

/*
 * DISPLAY TREE STRUCTURE
 * ----------------------
 * Shows tree with thread indicators
 */
void displayTree(struct Node* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    // Print right subtree (only if not threaded)
    if (!root->isThreaded && root->right != NULL) {
        displayTree(root->right, space);
    }
    
    // Print current node
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    
    if (root->isThreaded && root->right != NULL) {
        printf("%d ---> %d (thread)\n", root->data, root->right->data);
    }
    else if (root->isThreaded) {
        printf("%d ---> NULL (thread)\n", root->data);
    }
    else {
        printf("%d\n", root->data);
    }
    
    // Print left subtree
    displayTree(root->left, space);
}

/*
 * MAIN FUNCTION - DEMONSTRATES THREADED BST
 * -----------------------------------------
 */
int main() {
    struct Node* root = NULL;
    
    printf("=== THREADED BINARY SEARCH TREE ===\n\n");
    
    printf("Advantage: Inorder traversal WITHOUT recursion or stack!\n");
    printf("NULL right pointers are 'threaded' to point to inorder successor\n\n");
    
    // Insert values
    printf("Inserting values: 20, 10, 30, 5, 15, 25, 35\n\n");
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);
    
    /*
     * Tree structure:
     *         20
     *        /  \
     *      10    30
     *     /  \   / \
     *    5   15 25 35
     */
    
    printf("Tree structure (---> indicates thread):\n");
    displayTree(root, 0);
    
    // Inorder traversal (no recursion!)
    printf("\n\nInorder traversal (without recursion): ");
    inorder(root);
    
    // Preorder traversal
    printf("\n\nPreorder traversal (without recursion): ");
    preorder(root);
    
    // Search
    printf("\n\nSearching for 15: %s", search(root, 15) ? "Found" : "Not Found");
    printf("\nSearching for 100: %s", search(root, 100) ? "Found" : "Not Found");
    
    // Min and Max
    struct Node* minNode = findMin(root);
    struct Node* maxNode = findMax(root);
    printf("\n\nMinimum value: %d", minNode->data);
    printf("\nMaximum value: %d", maxNode->data);
    
    // Count nodes
    printf("\n\nTotal nodes: %d", countNodes(root));
    
    // Demonstrate finding successor
    printf("\n\nInorder successor of 10: ");
    struct Node* node = root->left;  // Node with value 10
    struct Node* succ = inorderSuccessor(node);
    if (succ != NULL) {
        printf("%d", succ->data);
    }
    
    printf("\n\nInorder successor of 15: ");
    node = root->left->right;  // Node with value 15
    succ = inorderSuccessor(node);
    if (succ != NULL) {
        printf("%d", succ->data);
    }
    
    printf("\n\n");
    return 0;
}
