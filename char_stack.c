#include <stdio.h>
#include "char_stack.h"
#include <stdlib.h>
#include <stdbool.h>

#define BASE_CAPACITY 10

// Tworzy nowy stos
CharStack* initCharStack() {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    if (!stack){
        printf("Błąd alokacji pamięci");
        exit(EXIT_FAILURE); // Kontrola błędu alokacji
    }   
    stack->top = -1; // Pusty stos

    stack->max_size = BASE_CAPACITY; // Początkowy rozmiar stosu

    stack->array = (char*)malloc(sizeof(char) * stack->max_size);// Tworzenie tablicy na elementy stosu
    
    if (!stack->array) { 
        free(stack);
        exit(EXIT_FAILURE); // Kontrola błędu alokacji
    }

    return stack;
}

// Dodaje element na stos
void pushChar(CharStack* stack, char data) {

    if (stack->top == stack->max_size - 1) { // Zwiększ rozmiar stosu, jeśli potrzeba
        stack->max_size *= 2;
        stack->array = (char*)realloc(stack->array, sizeof(char) * stack->max_size);
        if (!stack->array) exit(EXIT_FAILURE); // Kontrola błędu realokacji
    }

    stack->array[++stack->top] = data; // Dodaje element
}

// Usuwa wiele elementów ze stosu
void removeMultiChar(CharStack* stack, int amount) {
    stack->top -= amount;
    if (stack->top < -1) stack->top = -1; // Zapewnia, że top nie jest mniejsze niż -1
}

// Usuwa stos
void freeChar(CharStack* stack) {
    free(stack->array); 
    free(stack); 
}

// Funkcja pomocnicza do określania kierunku skrętu
const char* determineTurn(char from, char to) {
    if ((from == 'N' && to == 'E') || (from == 'E' && to == 'S') ||
        (from == 'S' && to == 'W') || (from == 'W' && to == 'N')) {
        return "RIGHT";
    } else {
        return "LEFT";
    }
}

int PrintMoves(CharStack* stack, const char* outputPath) {
    int moveCount = 0;

    FILE* output = fopen(outputPath, "w");
    if (!output) {
        fprintf(stderr, "Failed to open file for writing.\n");
        return -1;
    }

    fprintf(output, "BEGIN\n");

    char currentDir = 'E'; // Początkowy kierunek

    // Jeśli stos nie jest pusty i pierwszy ruch nie jest w tym samym kierunku co obecny kierunek
    if (stack->top >= 0 && stack->array[0] != currentDir) {
        determineTurn(currentDir, stack->array[0]);
        currentDir = stack->array[0];
    }

    int seqLength = 1; // Długość sekwencji ruchów w tym samym kierunku
    char lastDir = stack->array[0]; // Ostatni kierunek

    for (int i = 1; i <= stack->top; i++) {
        moveCount++;
        if (stack->array[i] == lastDir) {
            seqLength++;
        } else {
            fprintf(output, "MOVE %d\n", seqLength); 
            fprintf(output, "%s\n", determineTurn(lastDir, stack->array[i])); 

            lastDir = stack->array[i];
            seqLength = 1; 
        }
    }

    fprintf(output, "MOVE %d\n", seqLength); 
    fprintf(output, "END\n"); 
    fclose(output);
    return moveCount;
}
