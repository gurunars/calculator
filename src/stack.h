#ifndef STACK_G
#define STACK_G

#include "common.h"

typedef struct _Node {
    void* data;
    struct _Node* next;
    struct _Node* previous;
} Node;

typedef struct _Stack {
    Node *top;
    Node *bottom;
    int length;
} Stack;

Stack* createStack();
void deleteStack(Stack* stack);
void push(Stack* stack, void* data);
void* pop(Stack* stack);
bool hasItems(const Stack* stack);

#endif
