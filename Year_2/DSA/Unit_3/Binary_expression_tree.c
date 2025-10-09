#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define the structure for a tree node
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Inorder traversal (prints infix expression)
void inorder(Node* root) {
    if (root != NULL) {
        if (root->left && root->right) printf("(");
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
        if (root->left && root->right) printf(")");
    }
}

// Evaluate the expression tree
int eval(Node* root) {
    if (!root) return 0;
    // If leaf node, return its value
    if (!root->left && !root->right)
        return root->data - '0';
    // Evaluate left and right subtrees
    int l_val = eval(root->left);
    int r_val = eval(root->right);
    // Apply the operator
    switch (root->data) {
        case '+': return l_val + r_val;
        case '-': return l_val - r_val;
        case '*': return l_val * r_val;
        case '/': return l_val / r_val;
    }
    return 0;
}

int main() {
    // Build the tree for (3 + (2 * 5))
    Node* root = newNode('+');
    root->left = newNode('3');
    root->right = newNode('*');
    root->right->left = newNode('2');
    root->right->right = newNode('5');

    printf("Infix expression: ");
    inorder(root);
    printf("\n");

    printf("Evaluated result: %d\n", eval(root));

    // Free memory (not shown for brevity)
    return 0;
}