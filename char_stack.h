#ifndef CHAR_STACK_H
#define CHAR_STACK_H

typedef struct {
    FILE *file;
    int index;
} CharStack;

// Inicjalizuje nowy stos
CharStack* createCharStack(FILE*);

// Dodaje element na wierzchołek stosu
void pushChar(CharStack*, char);

// Usuwa i zwraca element z wierzchołka stosu
void popCharMultiple(CharStack*, int);

// Usuwa x elementów ze stosu
void deleteCharStack(CharStack*);

const char* getTurnDirection(char , char );

int printMoves(CharStack *, const char* name);

#endif // CHAR_STACK_H
