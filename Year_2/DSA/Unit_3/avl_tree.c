/*
 * AVL TREE - SELF-BALANCING BINARY SEARCH TREE
 * ============================================
 * 
 * What is an AVL Tree?
 * An AVL tree is a self-balancing BST where the heights of left and right
 * subtrees of any node differ by at most 1.
 * 
 * Why AVL Trees?
 * Regular BST can become skewed (like a linked list) in worst case.
 * Example: Inserting 1, 2, 3, 4, 5 in order creates:
 *   1
 *    \
 *     2
 *      \
 *       3  (Height = 4, very inefficient!)
 * 
 * AVL tree automatically balances itself to maintain O(log n) operations.
 * 
 * Key Concepts:
 * 1. Balance Factor = Height(Left Subtree) - Height(Right Subtree)
 * 2. For AVL tree, balance factor must be -1, 0, or 1
 * 3. If balance factor becomes -2 or 2, we perform rotations
 * 
 * Four Types of Rotations:
 * 1. Left-Left (LL): Right rotation
 * 2. Right-Right (RR): Left rotation
 * 3. Left-Right (LR): Left rotation then Right rotation
 * 4. Right-Left (RL): Right rotation then Left rotation
 */

#include <stdio.h>
#include <stdlib.h>

// Node structure with height field
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;  // Height of this node (for balance calculation)
};

/*
 * UTILITY FUNCTION: GET HEIGHT
 * ----------------------------
 * Returns height of a node (handles NULL case)
 */
int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

/*
 * UTILITY FUNCTION: GET MAXIMUM
 * -----------------------------
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/*
 * CREATE A NEW NODE
 * ----------------
 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;  // New node is initially at height 1
    return newNode;
}

/*
 * GET BALANCE FACTOR
 * ------------------
 * Balance Factor = Height(Left) - Height(Right)
 * 
 * If BF = 2: Left subtree is too tall (need right rotation)
 * If BF = -2: Right subtree is too tall (need left rotation)
 * If BF = -1, 0, 1: Tree is balanced
 */
int getBalanceFactor(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

/*
 * RIGHT ROTATION (Used for Left-Left case)
 * ----------------------------------------
 * 
 * Before rotation:        After rotation:
 *       z                      y
 *      / \                    / \
 *     y   T4    ------>      x   z
 *    / \                    / \ / \
 *   x  T3                 T1 T2 T3 T4
 *  / \
 * T1 T2
 * 
 * When to use: When left subtree is too tall and
 *              left child's left subtree is causing imbalance
 */
struct Node* rightRotate(struct Node* z) {
    // Store pointers
    struct Node* y = z->left;
    struct Node* T3 = y->right;
    
    // Perform rotation
    y->right = z;
    z->left = T3;
    
    // Update heights (update z first, then y)
    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    
    // Return new root
    return y;
}

/*
 * LEFT ROTATION (Used for Right-Right case)
 * -----------------------------------------
 * 
 * Before rotation:        After rotation:
 *     z                        y
 *    / \                      / \
 *   T1  y      ------>       z   x
 *      / \                  / \ / \
 *     T2  x               T1 T2 T3 T4
 *        / \
 *       T3 T4
 * 
 * When to use: When right subtree is too tall and
 *              right child's right subtree is causing imbalance
 */
struct Node* leftRotate(struct Node* z) {
    // Store pointers
    struct Node* y = z->right;
    struct Node* T2 = y->left;
    
    // Perform rotation
    y->left = z;
    z->right = T2;
    
    // Update heights
    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    
    // Return new root
    return y;
}

/*
 * INSERT A VALUE INTO AVL TREE
 * ----------------------------
 * Steps:
 * 1. Perform normal BST insertion
 * 2. Update height of current node
 * 3. Get balance factor
 * 4. If unbalanced, perform appropriate rotation
 */
struct Node* insert(struct Node* node, int value) {
    // Step 1: Perform normal BST insertion
    if (node == NULL) {
        return createNode(value);
    }
    
    if (value < node->data) {
        node->left = insert(node->left, value);
    }
    else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    else {
        // Duplicate values not allowed
        return node;
    }
    
    // Step 2: Update height of current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    
    // Step 3: Get balance factor
    int balance = getBalanceFactor(node);
    
    // Step 4: If unbalanced, there are 4 cases
    
    // Case 1: Left-Left (LL) - Right rotation needed
    // Left subtree is taller AND new value was inserted in left child's left subtree
    if (balance > 1 && value < node->left->data) {
        return rightRotate(node);
    }
    
    // Case 2: Right-Right (RR) - Left rotation needed
    // Right subtree is taller AND new value was inserted in right child's right subtree
    if (balance < -1 && value > node->right->data) {
        return leftRotate(node);
    }
    
    // Case 3: Left-Right (LR) - Left rotation then Right rotation
    // Left subtree is taller BUT new value was inserted in left child's right subtree
    if (balance > 1 && value > node->left->data) {
        node->left = leftRotate(node->left);  // First left rotate the left child
        return rightRotate(node);              // Then right rotate current node
    }
    
    // Case 4: Right-Left (RL) - Right rotation then Left rotation
    // Right subtree is taller BUT new value was inserted in right child's left subtree
    if (balance < -1 && value < node->right->data) {
        node->right = rightRotate(node->right);  // First right rotate the right child
        return leftRotate(node);                  // Then left rotate current node
    }
    
    // If tree is balanced, return unchanged node
    return node;
}

/*
 * FIND MINIMUM VALUE NODE
 * -----------------------
 * (Needed for deletion)
 */
struct Node* findMin(struct Node* node) {
    struct Node* current = node;
    
    // Go to leftmost node
    while (current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

/*
 * DELETE A VALUE FROM AVL TREE
 * ----------------------------
 * Similar to insertion:
 * 1. Perform normal BST deletion
 * 2. Update height
 * 3. Check balance and perform rotations if needed
 */
struct Node* deleteNode(struct Node* root, int value) {
    // Step 1: Perform standard BST deletion
    if (root == NULL) {
        return root;
    }
    
    // Find the node to delete
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        // Node found! Delete it
        
        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Case 2: Node with two children
        // Get inorder successor (smallest in right subtree)
        struct Node* temp = findMin(root->right);
        
        // Copy successor's data to this node
        root->data = temp->data;
        
        // Delete the successor
        root->right = deleteNode(root->right, temp->data);
    }
    
    // If tree had only one node, return
    if (root == NULL) {
        return root;
    }
    
    // Step 2: Update height of current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    
    // Step 3: Get balance factor
    int balance = getBalanceFactor(root);
    
    // Step 4: If unbalanced, perform rotations
    
    // Left-Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    
    // Left-Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right-Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    
    // Right-Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

/*
 * DISPLAY TREE STRUCTURE
 * ----------------------
 * Shows tree with indentation
 */
void displayTree(struct Node* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    // Print right subtree first (top of display)
    displayTree(root->right, space);
    
    // Print current node
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d(h=%d,bf=%d)\n", root->data, root->height, getBalanceFactor(root));
    
    // Print left subtree
    displayTree(root->left, space);
}

/*
 * INORDER TRAVERSAL
 * ----------------
 */
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/*
 * CHECK IF TREE IS BALANCED
 * -------------------------
 */
int isBalanced(struct Node* root) {
    if (root == NULL) {
        return 1;
    }
    
    int balance = getBalanceFactor(root);
    
    // Check if current node is balanced and recursively check subtrees
    return (balance >= -1 && balance <= 1) &&
           isBalanced(root->left) &&
           isBalanced(root->right);
}

/*
 * MAIN FUNCTION - DEMONSTRATES AVL TREE
 * -------------------------------------
 */
int main() {
    struct Node* root = NULL;
    
    printf("=== AVL TREE (SELF-BALANCING BST) ===\n\n");
    
    // Demonstrate the problem with regular BST
    printf("Problem: Inserting 10, 20, 30, 40, 50 in a regular BST creates skewed tree\n");
    printf("Solution: AVL tree automatically balances itself!\n\n");
    
    // Insert values
    printf("Inserting: 10, 20, 30, 40, 50, 25\n\n");
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    
    printf("Tree structure (h=height, bf=balance factor):\n");
    displayTree(root, 0);
    
    printf("\n\nInorder traversal (sorted): ");
    inorder(root);
    
    printf("\n\nIs tree balanced? %s", isBalanced(root) ? "Yes" : "No");
    printf("\nTree height: %d", getHeight(root));
    
    // Delete a node
    printf("\n\nDeleting 40...\n");
    root = deleteNode(root, 40);
    
    printf("\nTree structure after deletion:\n");
    displayTree(root, 0);
    
    printf("\n\nInorder traversal: ");
    inorder(root);
    
    printf("\n\nIs tree still balanced? %s", isBalanced(root) ? "Yes" : "No");
    
    printf("\n\n");
    return 0;
}
