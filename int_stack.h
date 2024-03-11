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

// Usuwa stos i zwalnia zaalokowaną pamięć
void deleteStack(Stack* stack);

bool isStackEmpty(Stack* stack);
