#include <stdbool.h>

typedef struct {
    int index; // wielkość stosu
    FILE *file;
} MiniIntStack;

// Prototypy funkcji dla mini stosu
MiniIntStack* initMiniInt(FILE *file); // Inicjalizuje nowy stos

void pushMiniInt(MiniIntStack* stack, short value); // Dodaje wartość na wierzch stosu

short removeMiniInt(MiniIntStack* stack); // Usuwa i zwraca wartość z wierzchu stosu

void freeMiniInt(MiniIntStack* stack); // Zwalnia pamięć zajmowaną przez stos
