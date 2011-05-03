#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* createStack(){
    Stack* tempo = malloc(sizeof(Stack));
    tempo->top = NULL;
    tempo->bottom = NULL;
    tempo->length = 0;
    return tempo;
}

void deleteStack(Stack* stack) {
    Node* next;
    Node* node = stack->bottom;
    while(node) {
        next = node->next;
        free(node);
        node = next;
    }
    free(stack);
}

bool hasItems(Stack* stack) {
    return stack->length;
}

void push(Stack* stack, void* data) {
    Node* node = stack->top;
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = new_node->previous = NULL;
    if (!node) {
        stack->bottom = new_node;
    } else {
        new_node->previous = node;
        node->next = new_node;
    }
    stack->top = new_node;
    stack->length++;
}

void* pop(Stack* stack){
    void* data;
    Node* node = stack->top;
    if (!stack->top) {
        return NULL;
    }
    if (node->previous) {
        node->previous->next = NULL;
        stack->top = node->previous;
    } else {
        stack->top = NULL;
        stack->bottom = NULL;
    }
    data = node->data;
    free(node);
    stack->length--;
    return data;
}
