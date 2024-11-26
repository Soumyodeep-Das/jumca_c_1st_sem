#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    double arr[MAX];
    int top;
} Stack;

void push(Stack *s, double val) {
    s->arr[++s->top] = val;
}

double pop(Stack *s) {
    return s->arr[s->top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int isOpeningBracket(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}

int isClosingBracket(char ch) {
    return ch == ')' || ch == '}' || ch == ']';
}

int bracketsMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

void infixToPostfix(char *infix, char *postfix) {
    Stack opStack = { .top = -1 };
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char token = infix[i];

        if (isdigit(token) || token == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            continue;
        } else if (isOpeningBracket(token)) {
            push(&opStack, token);
        } else if (isClosingBracket(token)) {
            while (opStack.top != -1 && !isOpeningBracket(opStack.arr[opStack.top])) {
                postfix[j++] = pop(&opStack);
                postfix[j++] = ' ';
            }
            if (opStack.top == -1 || !bracketsMatch(opStack.arr[opStack.top], token)) {
                printf("Error: Mismatched brackets\n");
                exit(EXIT_FAILURE);
            }
            pop(&opStack); // Remove the matching opening bracket
        } else if (strchr("+-*/", token)) {
            while (opStack.top != -1 && precedence(opStack.arr[opStack.top]) >= precedence(token)) {
                postfix[j++] = pop(&opStack);
                postfix[j++] = ' ';
            }
            push(&opStack, token);
        }
        i++;
    }

    while (opStack.top != -1) {
        postfix[j++] = pop(&opStack);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

double evaluatePostfix(char *postfix) {
    Stack valStack = { .top = -1 };
    int i = 0;

    while (postfix[i] != '\0') {
        char token = postfix[i];

        if (isdigit(token) || token == '.') {
            double num = 0.0, divisor = 1.0;
            int decimal = 0;

            while (isdigit(postfix[i]) || postfix[i] == '.') {
                if (postfix[i] == '.') {
                    decimal = 1;
                } else {
                    if (decimal) {
                        divisor *= 10.0;
                        num += (postfix[i] - '0') / divisor;
                    } else {
                        num = num * 10 + (postfix[i] - '0');
                    }
                }
                i++;
            }
            push(&valStack, num);
        } else if (strchr("+-*/", token)) {
            double b = pop(&valStack);
            double a = pop(&valStack);

            switch (token) {
                case '+': push(&valStack, a + b); break;
                case '-': push(&valStack, a - b); break;
                case '*': push(&valStack, a * b); break;
                case '/': push(&valStack, a / b); break;
            }
        }
        i++;
    }

    return pop(&valStack);
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("Result: %.2f\n", result);

    return 0;
}

