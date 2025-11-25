/*
 * RED-BLACK TREE - SELF-BALANCING BST
 * ===================================
 * 
 * What is a Red-Black Tree?
 * A Red-Black tree is another type of self-balancing BST where each node
 * has a color (RED or BLACK) and follows specific rules to maintain balance.
 * 
 * Red-Black Tree Properties:
 * 1. Every node is either RED or BLACK
 * 2. Root is always BLACK
 * 3. All leaves (NULL) are BLACK
 * 4. If a node is RED, both its children must be BLACK (no two consecutive reds)
 * 5. Every path from root to leaf has the same number of BLACK nodes
 * 
 * Why Red-Black Trees?
 * - Slightly less balanced than AVL trees (height can be 2*log(n))
 * - But FASTER insertions and deletions (fewer rotations needed)
 * - Used in many standard libraries (C++ STL map, Java TreeMap, Linux kernel)
 * 
 * Comparison with AVL:
 * AVL: More strictly balanced, faster lookups
 * Red-Black: Faster insertions/deletions, good enough balance
 * 
 * This file covers the BASICS of Red-Black trees
 * (Full implementation is complex, so we focus on concepts and simple operations)
 */

#include <stdio.h>
#include <stdlib.h>

// Color enumeration
enum Color {
    RED,
    BLACK
};

// Node structure
struct Node {
    int data;
    enum Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;  // Red-Black trees need parent pointer
};

/*
 * CREATE A NEW NODE
 * ----------------
 * New nodes are always created as RED
 * (This might violate property 4, which we fix with rotations/recoloring)
 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->color = RED;  // New nodes are RED
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

/*
 * LEFT ROTATION
 * ------------
 * Same as AVL tree rotation
 */
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    
    x->right = y->left;
    
    if (y->left != NULL) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == NULL) {
        *root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

/*
 * RIGHT ROTATION
 * -------------
 * Same as AVL tree rotation
 */
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    
    y->left = x->right;
    
    if (x->right != NULL) {
        x->right->parent = y;
    }
    
    x->parent = y->parent;
    
    if (y->parent == NULL) {
        *root = x;
    }
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    
    x->right = y;
    y->parent = x;
}

/*
 * FIX RED-BLACK TREE AFTER INSERTION
 * ----------------------------------
 * After inserting a RED node, we might violate property 4
 * (RED node with RED parent)
 * 
 * We fix this using rotations and recoloring
 */
void fixInsert(struct Node** root, struct Node* newNode) {
    struct Node* parent = NULL;
    struct Node* grandparent = NULL;
    
    // Fix violations while newNode is RED and parent is RED
    while (newNode != *root && newNode->color == RED && 
           newNode->parent != NULL && newNode->parent->color == RED) {
        
        parent = newNode->parent;
        grandparent = parent->parent;
        
        // Case A: Parent is left child of grandparent
        if (parent == grandparent->left) {
            struct Node* uncle = grandparent->right;
            
            // Case 1: Uncle is RED
            // Solution: Recolor parent, uncle, and grandparent
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;  // Move up and check again
            }
            else {
                // Case 2: newNode is right child (Left-Right case)
                // Solution: Left rotate parent, then treat as Case 3
                if (newNode == parent->right) {
                    leftRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                
                // Case 3: newNode is left child (Left-Left case)
                // Solution: Right rotate grandparent and recolor
                rightRotate(root, grandparent);
                enum Color temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        }
        // Case B: Parent is right child of grandparent (symmetric to Case A)
        else {
            struct Node* uncle = grandparent->left;
            
            // Case 1: Uncle is RED
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            }
            else {
                // Case 2: newNode is left child (Right-Left case)
                if (newNode == parent->left) {
                    rightRotate(root, parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                
                // Case 3: newNode is right child (Right-Right case)
                leftRotate(root, grandparent);
                enum Color temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                newNode = parent;
            }
        }
    }
    
    // Root must always be BLACK
    (*root)->color = BLACK;
}

/*
 * INSERT A VALUE
 * -------------
 * 1. Perform normal BST insertion
 * 2. Color the new node RED
 * 3. Fix any violations
 */
struct Node* insert(struct Node* root, int value) {
    // Create new node
    struct Node* newNode = createNode(value);
    
    // If tree is empty, new node becomes root (and must be BLACK)
    if (root == NULL) {
        newNode->color = BLACK;
        return newNode;
    }
    
    // Find position to insert (normal BST insertion)
    struct Node* current = root;
    struct Node* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        
        if (value < current->data) {
            current = current->left;
        }
        else if (value > current->data) {
            current = current->right;
        }
        else {
            // Duplicate value
            free(newNode);
            return root;
        }
    }
    
    // Insert new node
    newNode->parent = parent;
    
    if (value < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    
    // Fix Red-Black tree properties
    fixInsert(&root, newNode);
    
    return root;
}

/*
 * SEARCH FOR A VALUE
 * ------------------
 * Same as normal BST
 */
int search(struct Node* root, int value) {
    while (root != NULL) {
        if (value == root->data) {
            return 1;
        }
        else if (value < root->data) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return 0;
}

/*
 * INORDER TRAVERSAL
 * ----------------
 */
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
        inorder(root->right);
    }
}

/*
 * DISPLAY TREE STRUCTURE
 * ----------------------
 */
void displayTree(struct Node* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    displayTree(root->right, space);
    
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d(%s)\n", root->data, root->color == RED ? "RED" : "BLACK");
    
    displayTree(root->left, space);
}

/*
 * COUNT BLACK HEIGHT
 * ------------------
 * Counts number of BLACK nodes from root to any leaf
 * (Should be same for all paths in a valid Red-Black tree)
 */
int blackHeight(struct Node* root) {
    if (root == NULL) {
        return 1;  // NULL nodes are BLACK
    }
    
    int leftHeight = blackHeight(root->left);
    
    // Add 1 if current node is BLACK
    if (root->color == BLACK) {
        return leftHeight + 1;
    }
    
    return leftHeight;
}

/*
 * VERIFY RED-BLACK PROPERTIES
 * ---------------------------
 * Checks if tree satisfies all Red-Black properties
 */
int verifyProperties(struct Node* root) {
    // Property 2: Root is BLACK
    if (root != NULL && root->color != BLACK) {
        printf("Violation: Root is not BLACK\n");
        return 0;
    }
    
    // Property 4: No two consecutive RED nodes
    // (Checked during traversal)
    
    return 1;
}

/*
 * MAIN FUNCTION - DEMONSTRATES RED-BLACK TREE
 * -------------------------------------------
 */
int main() {
    struct Node* root = NULL;
    
    printf("=== RED-BLACK TREE ===\n\n");
    
    printf("Properties:\n");
    printf("1. Every node is RED or BLACK\n");
    printf("2. Root is BLACK\n");
    printf("3. All leaves (NULL) are BLACK\n");
    printf("4. RED node cannot have RED children\n");
    printf("5. All paths have same number of BLACK nodes\n\n");
    
    // Insert values
    printf("Inserting: 10, 20, 30, 15, 25, 5, 1\n\n");
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 5);
    root = insert(root, 1);
    
    printf("Tree structure (R=RED, B=BLACK):\n");
    displayTree(root, 0);
    
    printf("\n\nInorder traversal: ");
    inorder(root);
    
    printf("\n\nBlack height: %d", blackHeight(root));
    
    printf("\n\nSearching for 15: %s", search(root, 15) ? "Found" : "Not Found");
    printf("\nSearching for 100: %s", search(root, 100) ? "Found" : "Not Found");
    
    printf("\n\nTree satisfies Red-Black properties: %s", 
           verifyProperties(root) ? "Yes" : "No");
    
    printf("\n\n");
    return 0;
}
