#include <stdio.h>
#define MAX 100
struct Stack {
    int arr[MAX];
    int top;
};

void init(struct Stack* s) { s->top = -1; }

int isEmpty(struct Stack* s) { return s->top == -1; }

void push(struct Stack* s, int x) { if(s->top<MAX-1) s->arr[++s->top]=x; }

int pop(struct Stack* s) { return isEmpty(s)?-1:s->arr[s->top--]; }

int peek(struct Stack* s) { return isEmpty(s)?-1: s->arr[s->top]; }

int main() {
    struct Stack s; init(&s);
    push(&s, 10); push(&s, 20);
    printf("Top:%d\n", peek(&s));
    printf("Popped:%d\n", pop(&s));
    return 0;
}
