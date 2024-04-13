#include <stdio.h>
#include <stdlib.h>
#include "char_stack.h"
#include "load_maze.h"

// Funkcja tworząca nową dynamiczną tablicę znaków
CharStack* createCharStack(FILE *file) {
    CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
    stack->index = 0;
    stack->file = file;
    return stack;
}

// Funkcja dodająca znak na koniec dynamicznej tablicy
void pushChar(CharStack* stack, char element) {
    fseek(stack->file,stack->index, SEEK_SET);
    fputc(element, stack->file);
    stack->index++;
}

void popCharMultiple(CharStack* stack, int popAmount) {
    fseek(stack->file, -popAmount, SEEK_END);
    fputc(' ', stack->file);
    stack->index -= popAmount;
}

char getMove(CharStack* stack, int index) {
    fseek(stack->file, index, SEEK_SET);
    char x = fgetc(stack->file);
    return x;
}

// Funkcja usuwająca dynamiczną tablicę znaków
void deleteCharStack(CharStack* stack) {
    free(stack);
}

// Funkcja pomocnicza do zwracania kierunku skrętu
const char* getTurnDirection(char from, char to) {
    if ((from == 'N' && to == 'E') || (from == 'E' && to == 'S') ||
        (from == 'S' && to == 'W') || (from == 'W' && to == 'N')) {
        return "RIGHT";
    } else {
        return "LEFT";
    }
}

int printMoves(CharStack* stack, const char* filename) {

    int l_ruch = 0;


    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Nie można otworzyć pliku do zapisu.\n");
        return -1;
    }

    fprintf(file, "START\n");

    // Załóżmy, że orientacja początkowa to wschód ('E')
    char currentDirection = 'E'; // Początkowy kierunek
    if (stack->index > 0 && getMove(stack, 0) != currentDirection) {
        // Obróć się w kierunku pierwszego ruchu, jeśli to konieczne
        getTurnDirection(currentDirection, getMove(stack, 0));
        currentDirection = getMove(stack, 0);
    }

    int streak = 1;
    char previousDirection = getMove(stack, 0); // Zakładamy, że tablica nie jest pusta

    for (int i = 1; i < stack->index; i++) {
        
        l_ruch++;
        if (getMove(stack, i) == previousDirection) {
            streak++;
        } else {
            fprintf(file, "FORWARD %d\n", streak); // Wypisz poprzednią sekwencję ruchu
            fprintf(file, "%s\n", getTurnDirection(previousDirection, getMove(stack, i))); // Wypisz skręt

            previousDirection = getMove(stack, i);
            streak = 1; // Resetuj licznik ruchów w nowym kierunku
        }
    }

    // Wypisz ostatnią sekwencję ruchów
    fprintf(file, "FORWARD %d\n", streak);
    fprintf(file, "STOP\n"); // Zakończ sekwencję
    fclose(file);
    return l_ruch; // Zwróć 0, aby sygnalizować, że funkcja zakończyła się sukcesem
}

void addPathToFile(CharStack* stack, FILE* output, int col, int start) {
    char move;
    int indeks = start;
    for (int i = 0; i < stack->index; i++) {
        move = getMove(stack, i);
        switch (move)
        {
        case 'N':
            indeks -= col;
            break;
        case 'S':
            indeks += col;
            break;
        case 'E':
            indeks++;
            break;
        case 'W':
            indeks--;
            break;
        default:
            break;
        }
        writeCell(output, indeks, col, '*');
    }
}