#include "int_stack.h"
#include <stdlib.h>
#include <stdio.h>

// Inicjalizuje nowy stos
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

// Dodaje element na wierzchołek stosu
void push(Stack* stack, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Stack allocation problem");
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Usuwa i zwraca element z wierzchołka stosu. Jeśli stos jest pusty, zwraca -1.
int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        return -1; // Stos jest pusty
    }
    StackNode* temp = stack->top;
    int poppedData = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedData;
}

// Usuwa stos i zwalnia zaalokowaną pamięć
void deleteStack(Stack* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

//sprawdza czy stos jest pusty
bool isStackEmpty(Stack* stack) {
    if(stack->top == NULL) return true;
    return false;
}