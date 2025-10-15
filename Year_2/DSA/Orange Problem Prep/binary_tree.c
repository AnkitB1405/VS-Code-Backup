#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Create new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Tree traversals
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

// Tree operations
int findHeight(struct TreeNode* root) {
    if (root == NULL) return 0;
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(struct TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeafNodes(struct TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Binary Tree to Forest (convert to multiple trees by removing root)
void binaryTreeToForest(struct TreeNode* root, struct TreeNode* forest[], int* count) {
    if (root == NULL) return;
    
    if (root->left) {
        forest[(*count)++] = root->left;
        root->left = NULL;
    }
    if (root->right) {
        forest[(*count)++] = root->right;
        root->right = NULL;
    }
    
    binaryTreeToForest(root->left, forest, count);
    binaryTreeToForest(root->right, forest, count);
}

// Example: Check if tree is balanced
int isBalanced(struct TreeNode* root) {
    if (root == NULL) return 1;
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    
    if (abs(leftHeight - rightHeight) <= 1 && 
        isBalanced(root->left) && 
        isBalanced(root->right)) {
        return 1;
    }
    return 0;
}