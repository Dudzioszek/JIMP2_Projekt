#include <stdio.h>
#include <stdlib.h>
#include "short_stack.h"

// Funkcja tworząca nową dynamiczną tablicę znaków
ShortStack* createShortStack(int capacity) {
    ShortStack* stack = (ShortStack*)malloc(sizeof(ShortStack));
    stack->index = 0;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(short int));
    return stack;
}

// Funkcja dodająca znak na koniec dynamicznej tablicy
void pushShort(ShortStack* stack, int element) {
   if (stack->index == stack->capacity) {
        printf("STOS PELNY!!!");
        return;
    }
    stack->array[stack->index] = element;
    stack->index++;
}

int popShort(ShortStack* stack) {
    stack->index--;
    int temp = stack->array[stack->index];
    stack->array[stack->index] = -1;
    return temp;
}

// Funkcja usuwająca dynamiczną tablicę znaków
void deleteShortStack(ShortStack* stack) {
    free(stack->array);
    free(stack);
}