#ifndef CHAR_STACK_H
#define CHAR_STACK_H

typedef struct {
    FILE *file;
    int index;
} CharStack;

// Inicjalizuje nowy stos
CharStack* createCharStack(FILE*);

void pushChar(CharStack*, char); // Dodaje element na stos

// Usuwa i zwraca element z wierzchołka stosu
void popCharMultiple(CharStack*, int);

int PrintMoves(CharStack* stack, const char* outputPath); // Wypisuje ruchy na stosie do pliku

const char* getTurnDirection(char , char );

char getMove(CharStack*, int );

int printMoves(CharStack *, const char* name);

void deleteCharStack(CharStack *);

#endif // CHAR_STACK_H
