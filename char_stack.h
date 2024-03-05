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
void pushChar(CharStack* stack, char data);

// Usuwa i zwraca element z wierzchołka stosu
void popCharMultiple(CharStack* stack, int x);

// Usuwa x elementów ze stosu
void deleteCharStack(CharStack* stack);

#endif // CHAR_STACK_H
