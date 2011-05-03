#include <stdio.h>
#include <stdlib.h>
#define bool char
#define true 1
#define false 0


typedef struct node {
    void* data;
    struct node* next;
    struct node* previous;
} Node;


typedef struct stack {
    Node *top;
    Node *bottom;
    int length;
} Stack;


Stack* createStack(){
    Stack* tempo = malloc(sizeof(Stack));
    tempo->top = NULL;
    tempo->bottom = NULL;
    tempo->length = 0;
    return tempo;
}

bool deleteStack(Stack* stack) {
    Node* next;
    Node* node = stack->bottom;
    while(node) {
        next = node->next;
        free(node);
        node = next;
    }
    free(stack);
}

bool push(Stack* stack, void* data) {
    Node* node = stack->top;
    Node* new_node = malloc(sizeof(Node));
    new_node->previous = node;
    new_node->data = data;
    stack->top = new_node;
    if (!node) {
        node = new_node;
        stack->bottom = new_node;
    } else {
        node->next = new_node;
    }
    stack->length++;
    return true;
}

void* pop(Stack* stack){
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
    void* data = node->data;
    free(node);
    stack->length--;
    return data;
}

/*
// valgrind --tool=memcheck --leak-check=full
int main()
{
    Stack* stack = createStack();
    int one,two,three;
    one = 1;
    two = 2;
    three = 3;
    push(stack, &one);
    push(stack, &two);
    push(stack, &three);
    printf("%d\n", stack->length); //3
    int *buff;
    while(buff = (int*)pop(stack)) {
        printf("%d\n", *buff); //3,2,1
    }
    printf("%d\n", stack->length); //0
    deleteStack(stack);
}
*/
