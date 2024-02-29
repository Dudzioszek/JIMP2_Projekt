#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>

void loadMaze(const char* filename, char maze[MAZE_SIZE], int* rows, int* cols) {

    // Otwarcie pliku
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        exit(EXIT_FAILURE);
    }

    char line[MAX_SIZE + 2]; // +2 dla '\n' i '\0'
    int row = 0;
    *cols = 0;  // Zainicjowanie liczby kolumn na 0

    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        while (line[col] != '\n' && line[col] != '\0') {
            int index = row * MAX_SIZE + col;  // Obliczenie indeksu w tablicy jednowymiarowej
            maze[index] = line[col];
            col++;
        }
        if (*cols < col) *cols = col;
        row++;
    }
    *rows = row;

    fclose(file);
}

void printMaze(const char maze[MAZE_SIZE], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i * MAX_SIZE + j;  // Obliczenie indeksu w tablicy jednowymiarowej
            printf("%c", maze[index]);
        }
        printf("\n");
    }
}
