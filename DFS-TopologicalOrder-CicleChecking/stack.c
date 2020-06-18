#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

// Node structure
struct node {
    int value;
    Node *previous; 
};

// Stack structure
struct stack {
    Node *top;
    int size;
};

// Creates empty stack
Stack *StackCreate() {
    Stack *s = (Stack *) malloc(sizeof(Stack)); // memory allocation
    s->top = NULL;
    s->size = 0;
    return s;
}

// Checks if stack is empty
int StackIsEmpty(Stack *s) {
    if (s->size == 0) return 1; // empty
    return 0; // not empty
}

// Returns stack size
int StackSize(Stack *s) {
    return s->size;
}

// Returns top value
int StackTop(Stack *s) {
    if (StackIsEmpty(s)) return -1;
    return s->top->value;
}

// Adds new value
void StackPush(Stack *s, int value) {
    Node *n = (Node*) malloc(sizeof(Node));
    
    n->value = value;
    n->previous = s->top;
    s->top = n;
    s->size++;
}

// Remove top
int StackPop(Stack *s) {
    if (StackIsEmpty(s)) return -1;
    int value = s->top->value;
    
    Node *n = s->top;
    s->top = s->top->previous;
    n->previous = NULL; 
    free(n); 
    n = NULL;
    s->size--;
    
    return value;
}

// Ends stack and releases allocated memory
void StackFree(Stack **s) {
    if (*s != NULL)
        while ((*s)->top != NULL)
            StackPop(*s);
    
    free(*s);
    *s = NULL;
}

// Prints stack
void StackPrint(Stack *s) {
    Node *n = (Node*) malloc(sizeof(Node));
    
    n = s->top;
    
    while (n != NULL) {
        printf("%d ", n->value);
        n = n->previous;
    } printf("\n");
    free(n);
}