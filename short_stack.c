#include <stdio.h>
#include <stdlib.h>
#include "short_stack.h"
#include <stdlib.h>
#include <stdio.h>
#define START_SIZE 10


// Inicjalizuje nowy mini stos
MiniIntStack* initMiniInt(FILE *file) {
    MiniIntStack* stack = (MiniIntStack*)malloc(sizeof(MiniIntStack));
    if (stack == NULL) {
        printf("Błąd alokacji pamięci");
        exit(EXIT_FAILURE); // Kontrola niepowodzenia alokacji
    }

    stack->index = 0;
    stack->file = file;
    return stack;
}

// Dodaje wartość na wierzch stosu
void pushMiniInt(MiniIntStack* stack, short value) {
    fseek(stack->file, stack->index, SEEK_SET);
    fprintf(stack->file, "%7d\n", value);
    stack->index += 8;
}

// Usuwa i zwraca wartość z wierzchu stosu
short removeMiniInt(MiniIntStack* stack) {
    stack->index -= 8;
    fseek(stack->file, stack->index, SEEK_SET);
    int data;
    if (fscanf(stack->file, "%d", &data) != 1) {
        fprintf(stderr, "Błąd odczytu danych ze stosu.\n");
        exit(EXIT_FAILURE);
    }
    return data;
}

// Zwalnia pamięć zajmowaną przez stos
void freeMiniInt(MiniIntStack* stack) {
    if (stack != NULL) {
        free(stack);
    }
}
