#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// Definicja struktury dla elementu stosu
typedef struct StackNode {
    int data; // kordynaty labiryntu
    struct StackNode* next; // Wskaźnik na następny element stosu
} StackNode;

// Definicja struktury dla stosu
typedef struct Stack {
    StackNode* top; // Wskaźnik na wierzchołek stosu
} Stack;


// Inicjalizuje nowy stos
Stack* createStack();


// Dodaje element na wierzchołek stosu
void push(Stack* stack, int data);

// Usuwa i zwraca element z wierzchołka stosu
int pop(Stack* stack);

// Usuwa x elementów ze stosu
void popMultiple(Stack* stack, int x);

// Zwraca wartość na wierzchołku stosu bez usuwania jej
int peek(Stack* stack);

// Sprawdza, czy dana liczba znajduje się w stosie
bool contains(Stack* stack, int data);

// Usuwa stos i zwalnia zaalokowaną pamięć
void deleteStack(Stack* stack);



#endif // STACK_H
