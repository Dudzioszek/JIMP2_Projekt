#include <stdbool.h>

// Definicja struktury dla elementu stosu

typedef struct {
    int *array;
    int index;
    int capacity;
} IntStack;

// Inicjalizuje nowy stos
IntStack* createIntStack(int);

// Dodaje element na wierzchołek stosu
void pushInt(IntStack* stack, int data);

// Usuwa i zwraca element z wierzchołka stosu
int popInt(IntStack* stack);

// Usuwa stos i zwalnia zaalokowaną pamięć
void deleteIntStack(IntStack* stack);
