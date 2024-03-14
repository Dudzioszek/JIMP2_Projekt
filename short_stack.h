#include <stdbool.h>

// Definicja struktury dla elementu stosu

typedef struct {
    int *array;
    int index;
    int capacity;
} ShortStack;

// Inicjalizuje nowy stos
ShortStack* createShortStack();

// Dodaje element na wierzchołek stosu
void pushShort(ShortStack* stack, int data);

// Usuwa i zwraca element z wierzchołka stosu
int popShort(ShortStack* stack);

// Usuwa stos i zwalnia zaalokowaną pamięć
void deleteShortStack(ShortStack* stack);