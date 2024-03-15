#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#include <stdbool.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

// Definicja struktury dla stosu znakowego
typedef struct {
    char *array; // Tablica na elementy stosu
    int top; // Wskaźnik na wierzchołek stosu
    int max_size; // Rozmiar stosu
} CharStack;

// Funkcje

CharStack* initCharStack(); // Inicjalizuje nowy stos

void pushChar(CharStack*, char); // Dodaje element na stos

void removeMultiChar(CharStack*, int); // Usuwa wiele elementów ze stosu

void freeChar(CharStack*); // Usuwa stos

const char* determineTurn(char from, char to); // Funkcja pomocnicza do określania kierunku skrętu

int PrintMoves(CharStack* stack, const char* outputPath); // Wypisuje ruchy na stosie do pliku


#endif // CHAR_STACK_H
