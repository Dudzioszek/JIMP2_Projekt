#include <stdio.h>
#include "char_stack.h"
#include <stdlib.h>
#include <stdbool.h>

// Inicjalizuje nowy stos
CharStack* createCharStack() {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    if (!stack) {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

// Dodaje element na wierzchołek stosu
void pushChar(CharStack* stack, char data) {
    CharStackNode* newNode = (CharStackNode*)malloc(sizeof(CharStackNode));
    if (!newNode) {
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Usuwa x elementów ze stosu. 
void popCharMultiple(CharStack* stack, int x) {
    CharStackNode* temp;
    while (x-- > 0 && stack->top != NULL) {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}

//Zwraca dwa elementy ze stosu
void returnTwoElem(CharStack* stack, char* element1, char* element2) {
    CharStackNode* topNode = stack->top;
    *element1 = topNode->data;
    *element2 = topNode->next->data;
}

// Usuwa stos
void deleteCharStack(CharStack* stack) {
    while (stack->top != NULL) {
        popCharMultiple(stack, 1);
    }
    free(stack);
}

void reverseCharStack(CharStack* stack) {
    if (stack == NULL || stack->top == NULL || stack->top->next == NULL) {
        // Stos jest pusty lub ma tylko jeden element, więc nie ma potrzeby odwracania
        return;
    }

    CharStackNode *prevNode = NULL;
    CharStackNode *currentNode = stack->top;
    CharStackNode *nextNode = NULL;

    while (currentNode != NULL) {
        nextNode = currentNode->next; // Zapamiętaj następny element
        currentNode->next = prevNode; // Odwróć wskaźnik na następny element

        
        // Przesuń wskaźniki
        prevNode = currentNode;
        currentNode = nextNode;
    }

    // Popraw wskaźnik na wierzchołek stosu
    stack->top = prevNode;
}


// Funkcja pomocnicza do printmoves do zwracania nazwy kierunku podczas skrętu
char* getTurnDirection(char from, char to) {
    if ((from == 'N' && to == 'E') || (from == 'E' && to == 'S') ||
        (from == 'S' && to == 'W') || (from == 'W' && to == 'N')) {
        return "TURNRIGHT";
    } else {
        return "TURNLEFT";
    }
}



int printMoves(CharStack* stack, const char* filename) {

    // Odwracanie stosu, aby ruchy były w kolejności od początku do końca
    reverseCharStack(stack);

    // Zakładamy że ścieżka patrzy się na wschód
    char currentDirection = 'E';
    int movesCount = 0;


    // Otwieranie pliku do zapisu
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku do zapisu.\n");
        return -1;
    }

    fprintf(file, "START\n");

    // Wypisanie rozpoczęcia
    CharStackNode* current = stack->top;
    char nextDirection = (current != NULL) ? current->data : 'E'; // Domyślnie wschód, jeśli stos jest pusty


    // Jeśli pierwszy ruch nie jest na wschód, to musimy się obrócić
    if (current != NULL && nextDirection != 'E') {

        getTurnDirection(currentDirection, nextDirection);
        currentDirection = nextDirection;
    }

    while (current != NULL) {
        int streak = 1; // Zaczynamy od 1, ponieważ już jesteśmy na pierwszym ruchu w nowym kierunku
        char direction = current->data;
        current = current->next;


        // Zliczanie ruchów w tym samym kierunku
        while (current != NULL && current->data == direction) {
            streak++;
            current = current->next;
        }

        // Wypisanie instrukcji FORWARD z ilością wyliczonych kroków
        fprintf(file, "FORWARD %d\n", streak);
        movesCount += streak;

        
        if (current != NULL) { // Jeśli nie jesteśmy na końcu ścieżki
            // Sprawdzanie następnego kierunku
            nextDirection = current->data;
            if (nextDirection != direction) {
                // Wypisywanie instrukcji skrętu w zależności od kierunku
                fprintf(file, "%s\n", getTurnDirection(direction, nextDirection));
                currentDirection = nextDirection; // Aktualizacja aktualnego kierunku
            }
        }
    }

    fprintf(file, "STOP\n");

    fclose(file);
    return movesCount;
}