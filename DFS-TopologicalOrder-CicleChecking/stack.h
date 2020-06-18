#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;

Stack *StackCreate();
void StackFree(Stack **s);
int StackIsEmpty(Stack *s);
int StackSize(Stack *s);
int StackTop(Stack *s);
void StackPush(Stack *s, int val);
int StackPop(Stack *s);
void StackPrint(Stack *s);

#endif