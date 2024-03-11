#include "short_stack.h"
#include <stdlib.h>

// Initializes a new stack
ShortStack* createShortStack() {
    ShortStack* stack = (ShortStack*)malloc(sizeof(ShortStack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

// Adds element to the top of the stack
void pushShort(ShortStack* stack, short int data) {
    ShortStackNode* newNode = (ShortStackNode*)malloc(sizeof(ShortStackNode));
    if (newNode == NULL) {
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Removes and returns element from the top of the stack. If the stack is empty, returns -1.
short int popShort(ShortStack* stack) {
    if (isShortStackEmpty(stack)) {
        return -1; // Stack is empty
    }
    ShortStackNode* temp = stack->top;
    short int poppedData = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedData;
}

// Deletes the stack and frees the allocated memory
void deleteShortStack(ShortStack* stack) {
    while (!isShortStackEmpty(stack)) {
        popShort(stack); // Corrected function call
    }
    free(stack);
}

// Checks if the stack is empty
bool isShortStackEmpty(ShortStack* stack) {
    if(stack->top == NULL) return true;
    return false;
}
