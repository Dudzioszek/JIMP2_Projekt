#include <stdbool.h>


// Definicja typu dla stosu liczbowego
typedef struct {
    FILE *file;
    int index;
} IntStack;

// Prototypy funkcji dla stosu

IntStack* initInt(FILE*); // 

void pushInt(IntStack* stack, int value); // 

int removeInt(IntStack* stack); //

void freeInt(IntStack* stack); //
