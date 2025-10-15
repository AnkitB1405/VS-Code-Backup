#include <stdio.h>
#include <stdlib.h>

// BST Node structure
struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
};

// Create BST node
struct BSTNode* createBSTNode(int data) {
    struct BSTNode* newNode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// BST Insertion
struct BSTNode* bstInsert(struct BSTNode* root, int data) {
    if (root == NULL) return createBSTNode(data);
    
    if (data < root->data) {
        root->left = bstInsert(root->left, data);
    } else if (data > root->data) {
        root->right = bstInsert(root->right, data);
    }
    return root;
}

// BST Search
struct BSTNode* bstSearch(struct BSTNode* root, int key) {
    if (root == NULL || root->data == key) return root;
    
    if (key < root->data) return bstSearch(root->left, key);
    return bstSearch(root->right, key);
}

// Find minimum value node
struct BSTNode* findMin(struct BSTNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// BST Deletion
struct BSTNode* bstDelete(struct BSTNode* root, int key) {
    if (root == NULL) return root;
    
    if (key < root->data) {
        root->left = bstDelete(root->left, key);
    } else if (key > root->data) {
        root->right = bstDelete(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children
        struct BSTNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = bstDelete(root->right, temp->data);
    }
    return root;
}

// Iterative Inorder Traversal
void iterativeInorder(struct BSTNode* root) {
    struct BSTNode* current = root;
    struct BSTNode* stack[100];
    int top = -1;
    
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Iterative Preorder Traversal
void iterativePreorder(struct BSTNode* root) {
    if (root == NULL) return;
    
    struct BSTNode* stack[100];
    int top = -1;
    stack[++top] = root;
    
    while (top != -1) {
        struct BSTNode* node = stack[top--];
        printf("%d ", node->data);
        
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
}

// Check if tree is BST
int isBSTUtil(struct BSTNode* root, int min, int max) {
    if (root == NULL) return 1;
    
    if (root->data <= min || root->data >= max) return 0;
    
    return isBSTUtil(root->left, min, root->data) && 
           isBSTUtil(root->right, root->data, max);
}

int isBST(struct BSTNode* root) {
    return isBSTUtil(root, -1000000, 1000000);
}

// Example 1: Find kth smallest element
void kthSmallestUtil(struct BSTNode* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k) return;
    
    kthSmallestUtil(root->left, k, count, result);
    
    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }
    
    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(struct BSTNode* root, int k) {
    int count = 0;
    int result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}

// Example 2: Convert BST to sorted linked list
struct ListNode {
    int data;
    struct ListNode* next;
};

void bstToSortedListUtil(struct BSTNode* root, struct ListNode** head) {
    if (root == NULL) return;
    
    bstToSortedListUtil(root->right, head);
    
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = root->data;
    newNode->next = *head;
    *head = newNode;
    
    bstToSortedListUtil(root->left, head);
}

struct ListNode* bstToSortedList(struct BSTNode* root) {
    struct ListNode* head = NULL;
    bstToSortedListUtil(root, &head);
    return head;
}