#include <stdio.h>
#include <stdlib.h>
#include "short_stack.h"
#include <stdlib.h>
#include <stdio.h>
#define START_SIZE 10


// Inicjalizuje nowy mini stos
MiniIntStack* initMiniInt() {
    MiniIntStack* stack = (MiniIntStack*)malloc(sizeof(MiniIntStack));
    if (stack == NULL) {
        printf("Błąd alokacji pamięci");
        exit(EXIT_FAILURE); // Kontrola niepowodzenia alokacji
    }

    stack->top = -1; // Stos jest pusty
    stack->max_size = START_SIZE; // Rozmiar początkowy stosu
    stack->array = (short*)malloc(stack->max_size * sizeof(short));

    if (stack->array == NULL) { 
        free(stack); // W przypadku niepowodzenia zwolnij pamięć stack
        exit(EXIT_FAILURE);
    }
    return stack;
}

// Dodaje wartość na wierzch stosu
void pushMiniInt(MiniIntStack* stack, short value) {
    if (stack->top == stack->max_size - 1) {
        // Rozszerza stos, gdy nie ma więcej miejsca
        stack->max_size *= 2;
        stack->array = (short*)realloc(stack->array, stack->max_size * sizeof(short));
        if (stack->array == NULL) {
            exit(EXIT_FAILURE); // Kontrola niepowodzenia realokacji
        }
    }
    
    stack->array[++stack->top] = value;
}

// Usuwa i zwraca wartość z wierzchu stosu
short removeMiniInt(MiniIntStack* stack) {
    if (stack->top == -1) {
        return -1; // Pusty stos
    }
    return stack->array[stack->top--];
}

// Zwalnia pamięć zajmowaną przez stos
void freeMiniInt(MiniIntStack* stack) {
    free(stack->array); 
    free(stack); 
}
