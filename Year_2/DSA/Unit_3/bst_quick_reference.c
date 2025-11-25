/*
 * ============================================================================
 * BINARY SEARCH TREE - QUICK REFERENCE GUIDE FOR EXAMS
 * ============================================================================
 * 
 * This file is a CHEAT SHEET for quick revision before your exam.
 * It contains key concepts, formulas, and code snippets.
 * 
 * TABLE OF CONTENTS:
 * 1. BST Properties and Definitions
 * 2. Time Complexities
 * 3. Common Operations (Quick Code)
 * 4. BST Variations Comparison
 * 5. Important Formulas
 * 6. Common Exam Questions
 * 7. Tips and Tricks
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================================
 * 1. BST PROPERTIES AND DEFINITIONS
 * ============================================================================
 * 
 * BST Property:
 * - Left subtree values < Node value < Right subtree values
 * 
 * Height: Number of edges in longest path from root to leaf
 * - Empty tree: height = -1
 * - Single node: height = 0
 * 
 * Depth: Number of edges from root to a node
 * 
 * Balanced BST: |height(left) - height(right)| ≤ 1 for all nodes
 * 
 * Complete BST: All levels filled except possibly last, which is filled left to right
 * 
 * Full BST: Every node has 0 or 2 children
 * 
 * Perfect BST: All internal nodes have 2 children, all leaves at same level
 */

/*
 * ============================================================================
 * 2. TIME COMPLEXITIES
 * ============================================================================
 * 
 * Operation          | Average Case | Worst Case | Best Case
 * -------------------|--------------|------------|----------
 * Search             | O(log n)     | O(n)       | O(1)
 * Insert             | O(log n)     | O(n)       | O(1)
 * Delete             | O(log n)     | O(n)       | O(1)
 * Find Min/Max       | O(log n)     | O(n)       | O(1)
 * Inorder Traversal  | O(n)         | O(n)       | O(n)
 * 
 * Worst case occurs when tree is skewed (like a linked list)
 * Average case assumes balanced tree
 * 
 * Space Complexity:
 * - Storage: O(n) for n nodes
 * - Recursion stack: O(h) where h is height
 * 
 * AVL Tree Time Complexities (All operations):
 * - Search, Insert, Delete: O(log n) GUARANTEED
 * 
 * Red-Black Tree:
 * - Search, Insert, Delete: O(log n) GUARANTEED
 */

/*
 * ============================================================================
 * 3. COMMON OPERATIONS - QUICK CODE SNIPPETS
 * ============================================================================
 */

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// CREATE NODE
struct Node* createNode(int val) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = val;
    n->left = n->right = NULL;
    return n;
}

// INSERT (Recursive)
struct Node* insert(struct Node* root, int val) {
    if (root == NULL) return createNode(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}

// SEARCH
int search(struct Node* root, int val) {
    if (root == NULL) return 0;
    if (root->data == val) return 1;
    if (val < root->data) return search(root->left, val);
    return search(root->right, val);
}

// FIND MIN
struct Node* findMin(struct Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

// FIND MAX
struct Node* findMax(struct Node* root) {
    while (root && root->right) root = root->right;
    return root;
}

// DELETE NODE
struct Node* deleteNode(struct Node* root, int val) {
    if (root == NULL) return NULL;
    
    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    }
    else {
        // Node found
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Two children: get inorder successor
        struct Node* succ = findMin(root->right);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    return root;
}

// INORDER (Left-Root-Right) - Gives SORTED output
void inorder(struct Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// PREORDER (Root-Left-Right)
void preorder(struct Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// POSTORDER (Left-Right-Root)
void postorder(struct Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// HEIGHT
int height(struct Node* root) {
    if (root == NULL) return -1;
    int lh = height(root->left);
    int rh = height(root->right);
    return 1 + (lh > rh ? lh : rh);
}

// COUNT NODES
int count(struct Node* root) {
    if (root == NULL) return 0;
    return 1 + count(root->left) + count(root->right);
}

// IS BST (Check validity)
int isBSTUtil(struct Node* root, int min, int max) {
    if (root == NULL) return 1;
    if (root->data <= min || root->data >= max) return 0;
    return isBSTUtil(root->left, min, root->data) && 
           isBSTUtil(root->right, root->data, max);
}

// LOWEST COMMON ANCESTOR
struct Node* LCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;
    if (n1 < root->data && n2 < root->data) return LCA(root->left, n1, n2);
    if (n1 > root->data && n2 > root->data) return LCA(root->right, n1, n2);
    return root;
}

/*
 * ============================================================================
 * 4. BST VARIATIONS COMPARISON
 * ============================================================================
 * 
 * REGULAR BST:
 * - Simple implementation
 * - Can become unbalanced (O(n) worst case)
 * - No extra space per node
 * 
 * AVL TREE:
 * - Self-balancing (balance factor = -1, 0, or 1)
 * - Strictly balanced (height = O(log n))
 * - Fast lookups
 * - More rotations on insert/delete
 * - Extra space: 1 int per node (height)
 * - Rotations: LL, RR, LR, RL
 * 
 * RED-BLACK TREE:
 * - Self-balancing (using colors)
 * - Less strictly balanced than AVL
 * - Faster insert/delete (fewer rotations)
 * - Used in: C++ STL map/set, Java TreeMap, Linux kernel
 * - Extra space: 1 bit per node (color)
 * - Properties: Root is black, no two consecutive reds, same black height
 * 
 * THREADED BST:
 * - NULL pointers store threads to successor/predecessor
 * - Inorder traversal without recursion/stack
 * - Better space utilization
 * - Extra space: 1 bit per node (isThreaded flag)
 * 
 * WHEN TO USE WHAT:
 * - Frequent lookups → AVL Tree
 * - Frequent insertions/deletions → Red-Black Tree
 * - Need fast traversal → Threaded BST
 * - Simple application → Regular BST
 */

/*
 * ============================================================================
 * 5. IMPORTANT FORMULAS
 * ============================================================================
 * 
 * For a BST with n nodes:
 * 
 * 1. Maximum height = n - 1 (skewed tree)
 * 2. Minimum height = floor(log₂(n))
 * 
 * 3. Maximum nodes at level L = 2^L
 * 4. Maximum nodes in tree of height h = 2^(h+1) - 1
 * 
 * 5. For complete BST: height = floor(log₂(n))
 * 
 * 6. Number of leaf nodes in full BST = (n + 1) / 2
 * 7. Number of internal nodes in full BST = (n - 1) / 2
 * 
 * 8. For AVL tree with n nodes: height ≤ 1.44 * log₂(n)
 * 9. For Red-Black tree: height ≤ 2 * log₂(n + 1)
 * 
 * 10. Inorder traversal of BST gives SORTED sequence
 */

/*
 * ============================================================================
 * 6. COMMON EXAM QUESTIONS
 * ============================================================================
 * 
 * THEORY QUESTIONS:
 * 
 * Q1: What is the BST property?
 * A: Left subtree < Node < Right subtree
 * 
 * Q2: What traversal gives sorted output for BST?
 * A: Inorder traversal (Left-Root-Right)
 * 
 * Q3: How to find kth smallest element?
 * A: Inorder traversal, return kth element
 * 
 * Q4: What is the advantage of AVL over BST?
 * A: Guaranteed O(log n) operations, always balanced
 * 
 * Q5: What are the 4 types of rotations in AVL?
 * A: LL (Right rotation), RR (Left rotation), LR, RL
 * 
 * Q6: What is balance factor in AVL?
 * A: Height(Left) - Height(Right), must be -1, 0, or 1
 * 
 * Q7: What are Red-Black tree properties?
 * A: 1) Every node is red/black
 *    2) Root is black
 *    3) All leaves (NULL) are black
 *    4) Red node has black children
 *    5) Same black height for all paths
 * 
 * Q8: What is threaded BST?
 * A: BST where NULL pointers store threads to successor/predecessor
 * 
 * Q9: How to check if a tree is BST?
 * A: Use min-max approach or check if inorder is sorted
 * 
 * Q10: What is the successor of a node in BST?
 * A: If right child exists: leftmost node in right subtree
 *    Else: first ancestor where node is in left subtree
 * 
 * CODING QUESTIONS (Practice these!):
 * 1. Insert a node
 * 2. Delete a node (all 3 cases)
 * 3. Find kth smallest/largest
 * 4. Check if valid BST
 * 5. Find LCA
 * 6. Convert sorted array to BST
 * 7. Find floor and ceiling
 * 8. Range query
 * 9. Mirror a tree
 * 10. Find diameter
 */

/*
 * ============================================================================
 * 7. TIPS AND TRICKS FOR EXAM
 * ============================================================================
 * 
 * DEBUGGING TIPS:
 * - Always check for NULL before accessing node
 * - Remember: Inorder of BST should be sorted
 * - Draw the tree on paper for complex operations
 * 
 * COMMON MISTAKES TO AVOID:
 * 1. Forgetting to return updated root after insertion/deletion
 * 2. Not handling NULL cases
 * 3. Confusing left and right in rotations
 * 4. Forgetting to free memory in deletion
 * 5. Not updating parent pointers (in Red-Black trees)
 * 
 * QUICK CHECKS:
 * - Is your inorder traversal sorted? → Valid BST
 * - Does every path have same black nodes? → Valid Red-Black
 * - Is |BF| ≤ 1 for all nodes? → Valid AVL
 * 
 * MEMORY MANAGEMENT:
 * - Always use malloc() for new nodes
 * - Always free() when deleting nodes
 * - Check if malloc() returned NULL (good practice)
 * 
 * EXAM STRATEGY:
 * 1. Read question carefully (BST vs general tree?)
 * 2. Draw example tree
 * 3. Trace your algorithm on paper
 * 4. Handle base cases first
 * 5. Write clean, commented code
 * 6. Test with edge cases (empty tree, single node, skewed tree)
 */

/*
 * ============================================================================
 * QUICK REFERENCE: DELETE NODE CASES
 * ============================================================================
 * 
 * Case 1: Leaf node (no children)
 * Action: Simply remove it, return NULL
 * 
 * Case 2a: Only right child
 * Action: Replace node with right child
 * 
 * Case 2b: Only left child
 * Action: Replace node with left child
 * 
 * Case 3: Two children
 * Action: Find inorder successor (min in right subtree)
 *         Copy successor's value to current node
 *         Delete successor
 */

/*
 * ============================================================================
 * QUICK REFERENCE: AVL ROTATIONS
 * ============================================================================
 * 
 * LL Case (Left-Left): Balance Factor = 2, Left child's BF = 1
 * Action: Right rotation on current node
 * 
 * RR Case (Right-Right): BF = -2, Right child's BF = -1
 * Action: Left rotation on current node
 * 
 * LR Case (Left-Right): BF = 2, Left child's BF = -1
 * Action: Left rotation on left child, then right rotation on current
 * 
 * RL Case (Right-Left): BF = -2, Right child's BF = 1
 * Action: Right rotation on right child, then left rotation on current
 */

int main() {
    printf("=== BST QUICK REFERENCE GUIDE ===\n\n");
    printf("This file contains:\n");
    printf("1. BST Properties and Definitions\n");
    printf("2. Time Complexities\n");
    printf("3. Common Operations Code\n");
    printf("4. BST Variations Comparison\n");
    printf("5. Important Formulas\n");
    printf("6. Common Exam Questions\n");
    printf("7. Tips and Tricks\n\n");
    printf("Read through the comments above for quick revision!\n\n");
    
    // Quick example
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    
    printf("Sample BST created with: 50, 30, 70, 20, 40\n");
    printf("Inorder (sorted): ");
    inorder(root);
    printf("\nHeight: %d\n", height(root));
    printf("Total nodes: %d\n", count(root));
    printf("\nGood luck with your exam! 🎓\n\n");
    
    return 0;
}
