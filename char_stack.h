#ifndef CHAR_STACK_H
#define CHAR_STACK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *file;
    int index;
} CharStack;

// Inicjalizuje nowy stos
CharStack* createCharStack(FILE*);

void pushChar(CharStack*, char); // Dodaje element na stos

// Usuwa i zwraca element z wierzchołka stosu
void popCharMultiple(CharStack*, int);

int PrintMoves(CharStack*, const char*); // Wypisuje ruchy na stosie do pliku

const char* getTurnDirection(char , char );

char getMove(CharStack*, int );

int printMoves(CharStack *, const char*);

void deleteCharStack(CharStack *);

void addPathToFile(CharStack*, FILE*, int, int);

#endif // CHAR_STACK_H
