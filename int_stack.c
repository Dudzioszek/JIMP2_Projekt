#include <stdio.h>
#include <stdlib.h>
#include "int_stack.h"

#define INITIAL_CAPACITY 10

// Funkcja tworząca nową dynamiczną tablicę znaków
IntStack* createIntStack(int capacity) {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
    stack->index = 0;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Funkcja dodająca znak na koniec dynamicznej tablicy
void pushInt(IntStack* stack, int element) {
   if (stack->index == stack->capacity) {
        printf("STOS PELNY!!!");
        return;
    }
    stack->array[stack->index] = element;
    stack->index++;
}

int popInt(IntStack* stack) {
    stack->index--;
    int temp = stack->array[stack->index];
    stack->array[stack->index] = -1;
    return temp;
}

// Funkcja usuwająca dynamiczną tablicę znaków
void deleteIntStack(IntStack* stack) {
    free(stack->array);
    free(stack);
}