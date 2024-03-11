#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// Definicja struktury dla elementu stosu
typedef struct ShortStackNode {
    short int data; // kordynaty labiryntu
    struct ShortStackNode* next; // Wskaźnik na następny element stosu
} ShortStackNode;

// Definicja struktury dla stosu
typedef struct ShortStack {
    ShortStackNode* top; // Wskaźnik na wierzchołek stosu
} ShortStack;


// Inicjalizuje nowy stos
ShortStack* createShortStack();


// Dodaje element na wierzchołek stosu
void pushShort(ShortStack* stack, short int data);

// Usuwa i zwraca element z wierzchołka stosu
short int popShort(ShortStack* stack);

// Usuwa stos i zwalnia zaalokowaną pamięć
void deleteShortStack(ShortStack* stack);

bool isShortStackEmpty(ShortStack* stack);

#endif // STACK_H
