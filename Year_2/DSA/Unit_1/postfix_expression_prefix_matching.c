#include <stdio.h>
#include <ctype.h>
/*The C type header file stdlib.h contains the declaration of the exit() function*/
#include <stdlib.h>
#define MAX 100

int evalPostfix(char* exp) {
    int stack[MAX], top = -1;
    for (int i = 0; exp[i]; i++) {
        if (isdigit(exp[i]))
            stack[++top] = exp[i] - '0';
        else {
            int val2 = stack[top--];
            int val1 = stack[top--];
            switch (exp[i]) {
                case '+': stack[++top] = val1 + val2; break;
                case '-': stack[++top] = val1 - val2; break;
                case '*': stack[++top] = val1 * val2; break;
                case '/': stack[++top] = val1 / val2; break;
            }
        }
    }
    return stack[top];
}

int main() {
    char exp[50];
    printf("Enter postfix expression: ");
    scanf("%s", exp);
    printf("Postfix Evaluation: %d\n", evalPostfix(exp)); // 2+(3*1)-9= -4
    return 0;
}
