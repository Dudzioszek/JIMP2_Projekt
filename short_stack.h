#include <stdbool.h>

typedef struct {
    FILE *file; // tablica przechowująca elementy stosu
    int index; // wielkość stosu
} MiniIntStack;

// Prototypy funkcji dla mini stosu
MiniIntStack* initMiniInt(); // Inicjalizuje nowy stos

void pushMiniInt(MiniIntStack* stack, short value); // Dodaje wartość na wierzch stosu

short removeMiniInt(MiniIntStack* stack); // Usuwa i zwraca wartość z wierzchu stosu

void freeMiniInt(MiniIntStack* stack); // Zwalnia pamięć zajmowaną przez stos
