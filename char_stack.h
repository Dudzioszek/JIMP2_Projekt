#ifndef CHAR_STACK_H
#define CHAR_STACK_H

typedef struct {
    char *array;
    int index;
    int capacity;
} CharStack;

// Inicjalizuje nowy stos
CharStack* createCharStack();

// Dodaje element na wierzchołek stosu
void pushChar(CharStack*, char);

// Usuwa i zwraca element z wierzchołka stosu
void popCharMultiple(CharStack*, int);

// Usuwa x elementów ze stosu
void deleteCharStack(CharStack*);

#endif // CHAR_STACK_H
