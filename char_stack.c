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

// Usuwa stos. 
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

        // Zwolnij pamięć poprzedniego węzła, ponieważ nie będzie już używany
        free(prevNode);

        // Przesuń wskaźniki
        prevNode = currentNode;
        currentNode = nextNode;
    }

    // Popraw wskaźnik na wierzchołek stosu
    stack->top = prevNode;
}cj


// Wypisuje wszystkie elementy stosu do pliku
int printMoves(CharStack* stack, const char* filename) {
    int l_ruchow = 0;
    // Otwórz plik do zapisu
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku do zapisu.\n");
        return;
    }

    // Wypisz elementy stosu do pliku
    int streak = 0;
    CharStackNode* current = stack->top;
    while (current != NULL) {
        l_ruchow++;
        streak++;
        if(current->next == NULL || current->data != current->next->data) {
            fprintf(file, "%d %c\n", streak, current->data);
            streak = 0;
        }
        current = current->next;
    }

    // Zamknij plik
    fclose(file);

    return l_ruchow;
}