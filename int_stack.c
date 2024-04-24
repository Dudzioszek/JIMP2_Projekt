#include <stdio.h>
#include <stdlib.h>
#include "int_stack.h"

// Inicjalizacja nowego stosu
IntStack* initInt(FILE *file) {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
    if (stack == NULL) {
        fprintf(stderr, "Błąd alokacji pamięci dla stosu.\n");
        exit(EXIT_FAILURE);
    }
    stack->index = 0;
    stack->file = file;
    return stack;
}

// Dodawanie elementu do stosu
void pushInt(IntStack* stack, int value) {
    fseek(stack->file, stack->index, SEEK_SET);
    fprintf(stack->file, "%7d\n", value);
    stack->index += 8;
}

// Usuwanie elementu ze stosu
int removeInt(IntStack* stack) {
    stack->index -= 8;
    fseek(stack->file, stack->index, SEEK_SET);
    int data;
    if (fscanf(stack->file, "%d", &data) != 1) {
        fprintf(stderr, "Błąd odczytu danych ze stosu.\n");
        exit(EXIT_FAILURE);
    }
    return data;
}

// Zwalnianie pamięci stosu
void freeInt(IntStack* stack) {
    if (stack != NULL) {
        free(stack);
    }
}
