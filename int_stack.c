#include <stdio.h>
#include <stdlib.h>
#include "int_stack.h"
#include <stdlib.h>
#include <stdio.h>

#define BASE_SIZE 10

// Inicjalizacja nowego stosu
IntStack* initInt() {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack)); // 

    if (stack == NULL) {
        printf("Błąd alokacji pamięci");
        exit(EXIT_FAILURE); // Nieudana alokacja pamięci
    }
    stack->top = -1; // Stos jest pusty
    stack->max_size = BASE_SIZE;
    stack->array = (int*)malloc(stack->max_size * sizeof(int));
    
    if (stack->array == NULL) {
        free(stack); // Zwolnij pamięć przydzieloną dla struktury stosu, jeśli nie można przydzielić pamięci na elementy
        exit(EXIT_FAILURE);
    }

    return stack;
}

// Dodawanie elementu do stosu
void pushInt(IntStack* stack, int value) {

    if (stack->top == stack->max_size - 1) { // Jeśli potrzeba więcej miejsca
        stack->max_size *= 2; // Podwajamy rozmiar tablicy

        stack->array = (int*)realloc(stack->array, stack->max_size * sizeof(int));
        
        if (stack->array == NULL) {
            exit(EXIT_FAILURE); // Nieudana realokacja pamięci
        }
    }

    stack->array[++stack->top] = value; // Dodajemy element na stos
}

// Usuwanie elementu ze stosu
int removeInt(IntStack* stack) {
    if (stack->top == -1) { // Jeśli stos jest pusty
        return -1; 
    }
    return stack->array[stack->top--]; 
}

// Zwalnianie pamięci stosu
void freeInt(IntStack* stack) {
    free(stack->array); 
    free(stack); 
}