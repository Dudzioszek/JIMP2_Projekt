#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#include <stdbool.h>

typedef struct CharStackNode {
    char data; // kordynaty labiryntu
    struct CharStackNode* next; // Wskaźnik na następny element stosu
} CharStackNode;

typedef struct CharStack {
    CharStackNode* top;  // Wskaźnik na wierzchołek stosu
} CharStack;

// Inicjalizuje nowy stos
CharStack* createCharStack();

// Dodaje element na wierzchołek stosu
void pushChar(CharStack*, char);

// Usuwa i zwraca element z wierzchołka stosu
void popCharMultiple(CharStack*, int);

void returnTwoElem(CharStack*, char*, char*);

void reverseCharStack(CharStack* stack);

// Usuwa x elementów ze stosu
void deleteCharStack(CharStack*);

//wypisuje ruchy do pliku, zwraca liczbe ruchow
int printMoves(CharStack*, const char*);

#endif // CHAR_STACK_H
