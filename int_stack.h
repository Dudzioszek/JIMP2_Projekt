#include <stdbool.h>



// Definicja typu dla stosu liczbowego
typedef struct {
    int *array; // Tablica na elementy stosu
    int top; // Wskaźnik na wierzchołek stosu
    int max_size; // Rozmiar stosu
} IntStack;

// Prototypy funkcji dla stosu

IntStack* initInt(); // 

void pushInt(IntStack* stack, int value); // 

int removeInt(IntStack* stack); //

void freeInt(IntStack* stack); //
