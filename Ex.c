#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}


int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '\0';
}

char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char* infix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, j = 0;
    char postfix[strlen(infix)];

    for (i = 0; infix[i]; ++i) {
        char ch = infix[i];
        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                postfix[j++] = pop(stack);
            pop(stack);
        } else {
            while (!isEmpty(stack) && precedence(ch) <= precedence(peek(stack)))
                postfix[j++] = pop(stack);
            push(stack, ch);
        }
    }

    while (!isEmpty(stack))
        postfix[j++] = pop(stack);

    postfix[j] = '\0';
    printf("Postfix expression: %s\n", postfix);

    free(stack->array);
    free(stack);
}

int main() {
    char infix[100];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix);
    return 0;
}
