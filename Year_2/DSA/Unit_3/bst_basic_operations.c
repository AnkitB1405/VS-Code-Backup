/*
 * BINARY SEARCH TREE - BASIC OPERATIONS
 * =====================================
 * 
 * What is a Binary Search Tree (BST)?
 * A BST is a tree data structure where each node has at most 2 children.
 * 
 * BST Property (VERY IMPORTANT):
 * - All values in the LEFT subtree are SMALLER than the node's value
 * - All values in the RIGHT subtree are LARGER than the node's value
 * 
 * Example BST:
 *         50
 *        /  \
 *      30    70
 *     /  \   / \
 *   20  40 60  80
 * 
 * This file covers: Insert, Search, Delete, and Traversals
 */

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a single node in the BST
struct Node {
    int data;              // The value stored in this node
    struct Node* left;     // Pointer to left child (smaller values)
    struct Node* right;    // Pointer to right child (larger values)
};

/*
 * CREATE A NEW NODE
 * -----------------
 * This function creates a new node with the given value
 * malloc() allocates memory in the heap (dynamic memory)
 */
struct Node* createNode(int value) {
    // Allocate memory for a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    // Set the data
    newNode->data = value;
    
    // Initially, the new node has no children
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

/*
 * INSERT A VALUE INTO BST
 * -----------------------
 * We follow the BST property:
 * - If value < current node, go LEFT
 * - If value > current node, go RIGHT
 * - If we reach NULL, that's where we insert
 */
struct Node* insert(struct Node* root, int value) {
    // Base case: If tree is empty or we found the insertion point
    if (root == NULL) {
        return createNode(value);
    }
    
    // Recursive case: Decide whether to go left or right
    if (value < root->data) {
        // Value is smaller, so it belongs in the LEFT subtree
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        // Value is larger, so it belongs in the RIGHT subtree
        root->right = insert(root->right, value);
    }
    // If value == root->data, we don't insert duplicates (you can modify this)
    
    return root;
}

/*
 * SEARCH FOR A VALUE IN BST
 * -------------------------
 * Returns 1 if found, 0 if not found
 * Time Complexity: O(h) where h is height of tree
 */
int search(struct Node* root, int value) {
    // Base case 1: Tree is empty or we've gone past a leaf
    if (root == NULL) {
        return 0;  // Not found
    }
    
    // Base case 2: We found the value!
    if (root->data == value) {
        return 1;  // Found
    }
    
    // Recursive case: Search in left or right subtree
    if (value < root->data) {
        // Value would be in LEFT subtree (smaller values)
        return search(root->left, value);
    }
    else {
        // Value would be in RIGHT subtree (larger values)
        return search(root->right, value);
    }
}

/*
 * FIND MINIMUM VALUE IN BST
 * -------------------------
 * The minimum value is always the LEFTMOST node
 * (Keep going left until you can't go anymore)
 */
struct Node* findMin(struct Node* root) {
    // If tree is empty
    if (root == NULL) {
        return NULL;
    }
    
    // Keep going left until we reach the leftmost node
    while (root->left != NULL) {
        root = root->left;
    }
    
    return root;
}

/*
 * FIND MAXIMUM VALUE IN BST
 * -------------------------
 * The maximum value is always the RIGHTMOST node
 * (Keep going right until you can't go anymore)
 */
struct Node* findMax(struct Node* root) {
    // If tree is empty
    if (root == NULL) {
        return NULL;
    }
    
    // Keep going right until we reach the rightmost node
    while (root->right != NULL) {
        root = root->right;
    }
    
    return root;
}

/*
 * DELETE A NODE FROM BST
 * ----------------------
 * This is the most complex operation. Three cases:
 * 
 * Case 1: Node has NO children (leaf node)
 *         - Simply remove it
 * 
 * Case 2: Node has ONE child
 *         - Replace node with its child
 * 
 * Case 3: Node has TWO children
 *         - Find the inorder successor (smallest in right subtree)
 *         - Replace node's value with successor's value
 *         - Delete the successor
 */
struct Node* deleteNode(struct Node* root, int value) {
    // Base case: Tree is empty
    if (root == NULL) {
        return NULL;
    }
    
    // Step 1: Find the node to delete
    if (value < root->data) {
        // Value is in LEFT subtree
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        // Value is in RIGHT subtree
        root->right = deleteNode(root->right, value);
    }
    else {
        // We found the node to delete! (root->data == value)
        
        // Case 1: Node has NO children (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);  // Free the memory
            return NULL;
        }
        
        // Case 2a: Node has only RIGHT child
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        
        // Case 2b: Node has only LEFT child
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 3: Node has TWO children
        else {
            // Find the inorder successor (smallest value in right subtree)
            struct Node* successor = findMin(root->right);
            
            // Copy the successor's value to this node
            root->data = successor->data;
            
            // Delete the successor (it will be a leaf or have only right child)
            root->right = deleteNode(root->right, successor->data);
        }
    }
    
    return root;
}

/*
 * INORDER TRAVERSAL (Left -> Root -> Right)
 * -----------------------------------------
 * This prints values in SORTED order for a BST!
 * Example: For tree [50, 30, 70, 20, 40, 60, 80]
 * Output: 20 30 40 50 60 70 80
 */
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);           // Visit left subtree
        printf("%d ", root->data);     // Visit root
        inorder(root->right);          // Visit right subtree
    }
}

/*
 * PREORDER TRAVERSAL (Root -> Left -> Right)
 * ------------------------------------------
 * Useful for creating a copy of the tree
 * Example: For tree [50, 30, 70, 20, 40, 60, 80]
 * Output: 50 30 20 40 70 60 80
 */
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);     // Visit root
        preorder(root->left);          // Visit left subtree
        preorder(root->right);         // Visit right subtree
    }
}

/*
 * POSTORDER TRAVERSAL (Left -> Right -> Root)
 * -------------------------------------------
 * Useful for deleting the tree (delete children before parent)
 * Example: For tree [50, 30, 70, 20, 40, 60, 80]
 * Output: 20 40 30 60 80 70 50
 */
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);         // Visit left subtree
        postorder(root->right);        // Visit right subtree
        printf("%d ", root->data);     // Visit root
    }
}

/*
 * FIND HEIGHT OF BST
 * ------------------
 * Height = number of edges in longest path from root to leaf
 * Empty tree has height -1, single node has height 0
 */
int height(struct Node* root) {
    if (root == NULL) {
        return -1;
    }
    
    // Height = 1 + maximum of (left subtree height, right subtree height)
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

/*
 * COUNT TOTAL NODES IN BST
 * ------------------------
 */
int countNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    // Total = 1 (current node) + nodes in left + nodes in right
    return 1 + countNodes(root->left) + countNodes(root->right);
}

/*
 * MAIN FUNCTION - DEMONSTRATES ALL OPERATIONS
 * -------------------------------------------
 */
int main() {
    struct Node* root = NULL;  // Start with empty tree
    
    printf("=== BINARY SEARCH TREE OPERATIONS ===\n\n");
    
    // Insert values into BST
    printf("Inserting values: 50, 30, 70, 20, 40, 60, 80\n");
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    /*
     * Current tree structure:
     *         50
     *        /  \
     *      30    70
     *     /  \   / \
     *   20  40 60  80
     */
    
    // Display traversals
    printf("\nInorder Traversal (sorted): ");
    inorder(root);
    
    printf("\nPreorder Traversal: ");
    preorder(root);
    
    printf("\nPostorder Traversal: ");
    postorder(root);
    
    // Tree properties
    printf("\n\nHeight of tree: %d", height(root));
    printf("\nTotal nodes: %d", countNodes(root));
    
    // Search operations
    printf("\n\nSearching for 40: %s", search(root, 40) ? "Found" : "Not Found");
    printf("\nSearching for 100: %s", search(root, 100) ? "Found" : "Not Found");
    
    // Find min and max
    struct Node* minNode = findMin(root);
    struct Node* maxNode = findMax(root);
    printf("\n\nMinimum value: %d", minNode->data);
    printf("\nMaximum value: %d", maxNode->data);
    
    // Delete operations
    printf("\n\nDeleting 20 (leaf node)...");
    root = deleteNode(root, 20);
    printf("\nInorder after deletion: ");
    inorder(root);
    
    printf("\n\nDeleting 30 (node with two children)...");
    root = deleteNode(root, 30);
    printf("\nInorder after deletion: ");
    inorder(root);
    
    printf("\n\nDeleting 50 (root node)...");
    root = deleteNode(root, 50);
    printf("\nInorder after deletion: ");
    inorder(root);
    
    printf("\n\n");
    return 0;
}
