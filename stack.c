#include "stack.h"
#include <stdlib.h>

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
        return NULL;
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

// Usuwa x elementów ze stosu
void popMultiple(Stack* stack, int x) {
    while (x-- > 0 && !isStackEmpty(stack)) {
        pop(stack);
    }
}

// Zwraca wartość na wierzchołku stosu bez usuwania jej. Jeśli stos jest pusty, zwraca -1.
int peek(Stack* stack) {
    if (isStackEmpty(stack)) {
        return -1; // Stos jest pusty
    }
    return stack->top->data;
}

// Sprawdza, czy dana liczba znajduje się w stosie. Zwraca true jeśli tak
bool contains(Stack* stack, int data) {
    StackNode* current = stack->top;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Usuwa stos i zwalnia zaalokowaną pamięć
void deleteStack(Stack* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

