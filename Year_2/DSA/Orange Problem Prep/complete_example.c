/*
// Main function to test all implementations
int main() {
    printf("=== Testing Data Structures ===\n\n");
    
    // Test Singly Linked List
    printf("1. Singly Linked List:\n");
    struct Node* head = NULL;
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertBeginning(&head, 0);
    
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    
    // Test Stack
    printf("\n2. Stack Operations:\n");
    struct Stack s;
    initStack(&s);
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    printf("Popped: %d\n", pop(&s));
    printf("Top: %d\n", peek(&s));
    
    // Test Postfix Evaluation
    char postfix[] = "23+4*";
    printf("Postfix %s = %d\n", postfix, evaluatePostfix(postfix));
    
    // Test BST
    printf("\n3. Binary Search Tree:\n");
    struct BSTNode* bstRoot = NULL;
    bstRoot = bstInsert(bstRoot, 50);
    bstInsert(bstRoot, 30);
    bstInsert(bstRoot, 70);
    bstInsert(bstRoot, 20);
    bstInsert(bstRoot, 40);
    
    printf("Inorder: ");
    iterativeInorder(bstRoot);
    printf("\n");
    
    printf("3rd smallest: %d\n", kthSmallest(bstRoot, 3));
    
    // Test Josephus Problem
    printf("\n4. Josephus Problem:\n");
    printf("Josephus position for n=7, k=3: %d\n", josephusIterative(7, 3));
    
    // Test CPU Scheduling
    printf("\n5. CPU Scheduling:\n");
    struct Process processes[] = {
        {1, 10, 10},
        {2, 5, 5},
        {3, 8, 8}
    };
    roundRobinScheduling(processes, 3, 2);
    
    return 0;
}
*/