#include <stdio.h>
#include <stdlib.h>
#include "char_stack.h"

// Funkcja tworząca nową dynamiczną tablicę znaków
CharStack* createCharStack(int capacity) {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    stack->index = 0;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Funkcja dodająca znak na koniec dynamicznej tablicy
void pushChar(CharStack* stack, char element) {
    if (stack->index == stack->capacity) {
        printf("STOS PELNY!!!");
        return;
    }
    stack->array[stack->index] = element;
    stack->index++;
}

void popCharMultiple(CharStack* stack, int popAmount) {
    if (popAmount <= stack->index) {
        stack->index -= popAmount;
    } else {
        stack->index = 0; // Jeśli popAmount jest większy niż liczba elementów na stosie, usuwamy wszystkie elementy
    }
}


// Funkcja usuwająca dynamiczną tablicę znaków
void deleteCharStack(CharStack* stack) {
    free(stack->array);
    free(stack);
}

// Funkcja pomocnicza do zwracania kierunku skrętu
const char* getTurnDirection(char from, char to) {
    if ((from == 'N' && to == 'E') || (from == 'E' && to == 'S') ||
        (from == 'S' && to == 'W') || (from == 'W' && to == 'N')) {
        return "TURNRIGHT";
    } else {
        return "TURNLEFT";
    }
}

int printMoves(CharStack* stack, const char* filename) {

    int l_ruch = 0;


    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku do zapisu.\n");
        return -1;
    }

    fprintf(file, "START\n");

    // Załóżmy, że orientacja początkowa to wschód ('E')
    char currentDirection = 'E'; // Początkowy kierunek
    if (stack->index > 0 && stack->array[0] != currentDirection) {
        // Obróć się w kierunku pierwszego ruchu, jeśli to konieczne
        getTurnDirection(currentDirection, stack->array[0]);
        currentDirection = stack->array[0];
    }

    int streak = 1;
    char previousDirection = stack->array[0]; // Zakładamy, że tablica nie jest pusta

    for (int i = 1; i < stack->index; i++) {
        
        l_ruch++;
        if (stack->array[i] == previousDirection) {
            streak++;
        } else {
            fprintf(file, "FORWARD %d\n", streak); // Wypisz poprzednią sekwencję ruchu
            fprintf(file, "%s\n", getTurnDirection(previousDirection, stack->array[i])); // Wypisz skręt

            previousDirection = stack->array[i];
            streak = 1; // Resetuj licznik ruchów w nowym kierunku
        }
    }

    // Wypisz ostatnią sekwencję ruchów
    fprintf(file, "FORWARD %d\n", streak);
    fprintf(file, "STOP\n"); // Zakończ sekwencję
    fclose(file);
    return l_ruch; // Zwróć 0, aby sygnalizować, że funkcja zakończyła się sukcesem
}