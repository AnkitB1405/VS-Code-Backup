#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack using array
struct Stack {
    int top;
    int items[MAX];
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[s->top--];
}

int peek(struct Stack* s) {
    if (isEmpty(s)) return -1;
    return s->items[s->top];
}

// Example 1: Prefix evaluation
int evaluatePrefix(char* expression) {
    struct Stack stack;
    initStack(&stack);
    
    int length = strlen(expression);
    
    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(expression[i])) {
            push(&stack, expression[i] - '0');
        } else {
            int operand1 = pop(&stack);
            int operand2 = pop(&stack);
            
            switch (expression[i]) {
                case '+': push(&stack, operand1 + operand2); break;
                case '-': push(&stack, operand1 - operand2); break;
                case '*': push(&stack, operand1 * operand2); break;
                case '/': push(&stack, operand1 / operand2); break;
            }
        }
    }
    return pop(&stack);
}

// Example 2: Postfix evaluation
int evaluatePostfix(char* expression) {
    struct Stack stack;
    initStack(&stack);
    
    for (int i = 0; expression[i]; i++) {
        if (isdigit(expression[i])) {
            push(&stack, expression[i] - '0');
        } else {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            
            switch (expression[i]) {
                case '+': push(&stack, operand1 + operand2); break;
                case '-': push(&stack, operand1 - operand2); break;
                case '*': push(&stack, operand1 * operand2); break;
                case '/': push(&stack, operand1 / operand2); break;
            }
        }
    }
    return pop(&stack);
}

// Infix to Postfix conversion
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return -1;
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack stack;
    initStack(&stack);
    int k = 0;
    
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[k++] = pop(&stack);
            }
            pop(&stack); // Remove '('
        } else {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
    }
    
    while (!isEmpty(&stack)) {
        postfix[k++] = pop(&stack);
    }
    postfix[k] = '\0';
}