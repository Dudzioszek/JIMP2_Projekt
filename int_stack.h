#include <stdbool.h>

// Definicja typu dla stosu liczbowego
typedef struct {
    int index; // Tablica na elementy stosu
    FILE *file; // Wskaźnik na wierzchołek stosu
} IntStack;

// Prototypy funkcji dla stosu

IntStack* initInt(FILE *file); // 

void pushInt(IntStack* stack, int value); // 

int removeInt(IntStack* stack); //

void freeInt(IntStack* stack); //
