#include <stdbool.h>

typedef struct {
    short *array; // tablica przechowująca elementy stosu
    int top; // wielkość stosu
    int max_size; // maksymalna wielkość stosu
} MiniIntStack;

// Prototypy funkcji dla mini stosu
MiniIntStack* initMiniInt(); // Inicjalizuje nowy stos

void pushMiniInt(MiniIntStack* stack, short value); // Dodaje wartość na wierzch stosu

short removeMiniInt(MiniIntStack* stack); // Usuwa i zwraca wartość z wierzchu stosu

void freeMiniInt(MiniIntStack* stack); // Zwalnia pamięć zajmowaną przez stos
