#include "char_Stack.h"
#include <stdlib.h>
#include <stdbool.h>


// Inicjalizuje nowy stos
CharStack* createCharStack() {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    if (!stack) {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}


// Dodaje element na wierzchołek stosu
void pushChar(CharStack* stack, char data) {
    CharStackNode* newNode = (CharStackNode*)malloc(sizeof(CharStackNode));
    if (!newNode) {
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Usuwa i zwraca element z wierzchołka stosu. 
void popCharMultiple(CharStack* stack, int x) {
    CharStackNode* temp;
    while (x-- > 0 && stack->top != NULL) {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}


// Zwraca wartość na wierzchołku stosu bez usuwania jej. 
void deleteCharStack(CharStack* stack) {
    while (stack->top != NULL) {
        popCharMultiple(stack, 1);
    }
    free(stack);
}
