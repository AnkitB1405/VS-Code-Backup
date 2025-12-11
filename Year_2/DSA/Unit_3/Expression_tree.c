/*
 * EXPRESSION TREE
 * ===============
 * 
 * What is an Expression Tree?
 * An expression tree is a binary tree where:
 * - LEAF nodes contain OPERANDS (numbers/variables)
 * - INTERNAL nodes contain OPERATORS (+, -, *, /, etc.)
 * 
 * Example: Expression "3 + 5 * 2"
 * 
 *         +
 *        / \
 *       3   *
 *          / \
 *         5   2
 * 
 * Uses:
 * - Evaluate mathematical expressions
 * - Convert between infix, prefix, postfix notations
 * - Compilers use this for expression evaluation
 * 
 * This code builds expression tree from POSTFIX expression
 * Why postfix? Because it's easier to build tree from postfix!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node structure for expression tree
struct Node {
    char data;              // Can be operator (+, -, *, /) or operand (digit/variable)
    struct Node* left;      // Left child
    struct Node* right;     // Right child
};

/*
 * CREATE A NEW NODE
 * -----------------
 * Creates a node with given character (operator or operand)
 */
struct Node* createNode(char value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/*
 * CHECK IF CHARACTER IS AN OPERATOR
 * ----------------------------------
 * Returns 1 if character is +, -, *, /
 * Returns 0 otherwise
 */
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/*
 * STACK IMPLEMENTATION FOR TREE NODES
 * ------------------------------------
 * We need a stack to build expression tree from postfix
 * Stack will store pointers to tree nodes
 */
#define MAX_SIZE 100

struct Stack {
    struct Node* arr[MAX_SIZE];
    int top;
};

// Initialize stack
void initStack(struct Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Push a node onto stack
void push(struct Stack* s, struct Node* node) {
    if (s->top >= MAX_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    s->arr[++(s->top)] = node;
}

// Pop a node from stack
struct Node* pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
        return NULL;
    }
    return s->arr[(s->top)--];
}

/*
 * BUILD EXPRESSION TREE FROM POSTFIX
 * -----------------------------------
 * Algorithm:
 * 1. Scan postfix expression from left to right
 * 2. If operand: Create node and push to stack
 * 3. If operator: 
 *    - Pop two nodes from stack (right, then left)
 *    - Create operator node with these as children
 *    - Push new node to stack
 * 4. Final node in stack is the root
 * 
 * Example: Postfix "ab+c*"
 * Step 1: See 'a' → push node(a)
 * Step 2: See 'b' → push node(b)
 * Step 3: See '+' → pop b, pop a, create +(a,b), push it
 * Step 4: See 'c' → push node(c)
 * Step 5: See '*' → pop c, pop +, create *(+,c), push it
 * Result: Root is *
 */
struct Node* buildExpressionTree(char postfix[]) {
    struct Stack s;
    initStack(&s);
    
    int len = strlen(postfix);
    
    // Scan each character in postfix expression
    for (int i = 0; i < len; i++) {
        char c = postfix[i];
        
        // Skip spaces
        if (c == ' ') {
            continue;
        }
        
        // If operand (letter or digit), create leaf node
        if (isalnum(c)) {
            struct Node* node = createNode(c);
            push(&s, node);
        }
        // If operator, create internal node
        else if (isOperator(c)) {
            // Create operator node
            struct Node* node = createNode(c);
            
            // Pop two operands from stack
            // IMPORTANT: First pop is RIGHT child, second pop is LEFT child
            node->right = pop(&s);
            node->left = pop(&s);
            
            // Push the new subtree back to stack
            push(&s, node);
        }
    }
    
    // The final node in stack is the root of expression tree
    return pop(&s);
}

/*
 * INORDER TRAVERSAL (Left-Root-Right)
 * ------------------------------------
 * For expression tree, this gives INFIX expression
 * Example: For tree of "ab+c*", inorder gives "a+b*c"
 * 
 * Note: We add parentheses to make precedence clear
 */
void inorder(struct Node* root) {
    if (root != NULL) {
        // If operator node, add opening parenthesis
        if (isOperator(root->data)) {
            printf("(");
        }
        
        inorder(root->left);           // Left subtree
        printf("%c", root->data);      // Root
        inorder(root->right);          // Right subtree
        
        // If operator node, add closing parenthesis
        if (isOperator(root->data)) {
            printf(")");
        }
    }
}

/*
 * PREORDER TRAVERSAL (Root-Left-Right)
 * -------------------------------------
 * For expression tree, this gives PREFIX expression
 * Example: For tree of "ab+c*", preorder gives "*+abc"
 */
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%c", root->data);      // Root
        preorder(root->left);          // Left subtree
        preorder(root->right);         // Right subtree
    }
}

/*
 * POSTORDER TRAVERSAL (Left-Right-Root)
 * --------------------------------------
 * For expression tree, this gives POSTFIX expression
 * Example: For tree of "ab+c*", postorder gives "ab+c*"
 */
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);         // Left subtree
        postorder(root->right);        // Right subtree
        printf("%c", root->data);      // Root
    }
}

/*
 * EVALUATE EXPRESSION TREE
 * -------------------------
 * Recursively evaluate the expression
 * 
 * Logic:
 * - If leaf node (operand): Return its numeric value
 * - If operator node: 
 *   1. Evaluate left subtree
 *   2. Evaluate right subtree
 *   3. Apply operator and return result
 * 
 * Note: This works only for single-digit numbers
 */
int evaluate(struct Node* root) {
    // Base case: Leaf node (operand)
    if (root->left == NULL && root->right == NULL) {
        // Convert character digit to integer
        return root->data - '0';
    }
    
    // Recursive case: Operator node
    // Evaluate left and right subtrees
    int leftValue = evaluate(root->left);
    int rightValue = evaluate(root->right);
    
    // Apply the operator
    switch (root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            if (rightValue == 0) {
                printf("Error: Division by zero!\n");
                return 0;
            }
            return leftValue / rightValue;
        default:
            return 0;
    }
}

/*
 * COUNT LEAF NODES (OPERANDS)
 * ---------------------------
 * Counts number of operands in expression
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
 * COUNT OPERATOR NODES
 * --------------------
 * Counts number of operators in expression
 */
int countOperators(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    
    // If operator node (has children)
    if (root->left != NULL || root->right != NULL) {
        return 1 + countOperators(root->left) + countOperators(root->right);
    }
    
    return 0;
}

/*
 * FIND HEIGHT OF EXPRESSION TREE
 * -------------------------------
 * Height indicates complexity of expression
 */
int height(struct Node* root) {
    if (root == NULL) {
        return -1;
    }
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

/*
 * DISPLAY TREE STRUCTURE
 * -----------------------
 * Visual representation of the tree
 */
void displayTree(struct Node* root, int space) {
    if (root == NULL) {
        return;
    }
    
    space += 5;
    
    // Print right subtree first (appears at top)
    displayTree(root->right, space);
    
    // Print current node
    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%c\n", root->data);
    
    // Print left subtree
    displayTree(root->left, space);
}

/*
 * MAIN FUNCTION - DEMONSTRATES EXPRESSION TREE
 * --------------------------------------------
 */
int main() {
    printf("=== EXPRESSION TREE ===\n\n");
    
    // Example 1: Simple expression
    printf("Example 1: Postfix expression \"35+2*\"\n");
    printf("This represents: (3 + 5) * 2\n\n");
    
    char postfix1[] = "35+2*";
    struct Node* root1 = buildExpressionTree(postfix1);
    
    printf("Tree structure:\n");
    displayTree(root1, 0);
    
    printf("\nTraversals:\n");
    printf("Infix (with parentheses):  ");
    inorder(root1);
    printf("\n");
    
    printf("Prefix:                    ");
    preorder(root1);
    printf("\n");
    
    printf("Postfix:                   ");
    postorder(root1);
    printf("\n");
    
    printf("\nEvaluation: %d\n", evaluate(root1));
    printf("Number of operands: %d\n", countLeaves(root1));
    printf("Number of operators: %d\n", countOperators(root1));
    printf("Height: %d\n", height(root1));
    
    // Example 2: More complex expression
    printf("\n\n===========================================\n\n");
    printf("Example 2: Postfix expression \"ab+cd-*\"\n");
    printf("This represents: (a + b) * (c - d)\n\n");
    
    char postfix2[] = "ab+cd-*";
    struct Node* root2 = buildExpressionTree(postfix2);
    
    printf("Tree structure:\n");
    displayTree(root2, 0);
    
    printf("\nTraversals:\n");
    printf("Infix (with parentheses):  ");
    inorder(root2);
    printf("\n");
    
    printf("Prefix:                    ");
    preorder(root2);
    printf("\n");
    
    printf("Postfix:                   ");
    postorder(root2);
    printf("\n");
    
    printf("\nNumber of operands: %d\n", countLeaves(root2));
    printf("Number of operators: %d\n", countOperators(root2));
    printf("Height: %d\n", height(root2));
    
    // Example 3: Expression with evaluation
    printf("\n\n===========================================\n\n");
    printf("Example 3: Postfix expression \"53+82-*\"\n");
    printf("This represents: (5 + 3) * (8 - 2)\n\n");
    
    char postfix3[] = "53+82-*";
    struct Node* root3 = buildExpressionTree(postfix3);
    
    printf("Tree structure:\n");
    displayTree(root3, 0);
    
    printf("\nInfix expression: ");
    inorder(root3);
    printf("\n");
    
    printf("\nStep-by-step evaluation:\n");
    printf("5 + 3 = 8\n");
    printf("8 - 2 = 6\n");
    printf("8 * 6 = 48\n");
    printf("\nFinal result: %d\n", evaluate(root3));
    
    printf("\n\n=== KEY POINTS ===\n");
    printf("1. Expression tree is built from POSTFIX notation\n");
    printf("2. Leaf nodes = Operands (numbers/variables)\n");
    printf("3. Internal nodes = Operators (+, -, *, /)\n");
    printf("4. Inorder traversal → Infix expression\n");
    printf("5. Preorder traversal → Prefix expression\n");
    printf("6. Postorder traversal → Postfix expression\n");
    printf("7. Evaluation is done using postorder (bottom-up)\n\n");
    
    return 0;
}
