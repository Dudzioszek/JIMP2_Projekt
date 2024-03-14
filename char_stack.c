#include <stdio.h>
#include <stdlib.h>
#include "char_stack.h"

#define INITIAL_CAPACITY 10

// Funkcja tworząca nową dynamiczną tablicę znaków
CharStack* createCharStack() {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    stack->index = 0;
    stack->capacity = INITIAL_CAPACITY;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Funkcja dodająca znak na koniec dynamicznej tablicy
void pushChar(CharStack* stack, char element) {
    if (stack->index == stack->capacity) {
        // Zwiększamy pojemność dwukrotnie
        stack->capacity *= 2;
        stack->array = (char*)realloc(stack->array, stack->capacity * sizeof(char));
    }
    stack->array[stack->index] = element;
    stack->index++;
}

void popCharMultiple(CharStack* stack, int popAmount) {
    int i = 0;
    while(i < popAmount) {
        stack->array[stack->index] = 'X';
        stack->index--;
        i++;
    }
}

// Funkcja usuwająca dynamiczną tablicę znaków
void deleteCharStack(CharStack* stack) {
    free(stack->array);
    free(stack);
}