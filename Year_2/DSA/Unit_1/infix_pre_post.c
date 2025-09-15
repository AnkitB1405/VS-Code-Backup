// Example to convert infix "A+B*C" to postfix and prefix
// (Just expression structure, not eval)

#include <stdio.h>

int main() {
    char infix[] = "A+B*C";
    char postfix[] = "ABC*+";
    char prefix[] = "+A*BC";
    printf("Infix: %s\n", infix);
    printf("Postfix: %s\n", postfix);
    printf("Prefix: %s\n", prefix);
    return 0;
}
/*
 * This program demonstrates how to convert an infix expression
 * into a postfix or prefix expression.
 *
 * Infix expressions are commonly used in mathematical notation, e.g.
 * 2 + 3 * 4. To evaluate this expression, we need to follow
 * the order of operations (PEMDAS) and evaluate the expression accordingly.
 *
 * Postfix expressions are commonly used in programming languages, e.g.
 * 2 3 4 * +. To evaluate this expression, we simply iterate
 * through the expression from left to right and evaluate each operator
 * as we encounter it.
 *
 * Prefix expressions are commonly used in programming languages, e.g.
 * + 2 * 3 4. To evaluate this expression, we simply iterate
 * through the expression from left to right and evaluate each operator
 * as we encounter it.
 *
 * This program can be used in any application that needs to parse
 * and evaluate mathematical expressions.
 */
