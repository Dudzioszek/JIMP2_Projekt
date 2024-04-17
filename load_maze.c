#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



MazeDim analyzeMazeAndFindPositions(FILE *file) {
    int cols = 0;
    int ch;
    // Zczytywanie liczby kolumn do pierwszego znaku nowej linii
    while ((ch = getc(file)) != '\n' && ch != EOF) {
        cols++;
    }

    if (cols == 0) {
        perror("Plik jest pusty lub błąd przy czytaniu pierwszej linii");
        exit(EXIT_FAILURE);
    }

    // Alokacja pamięci na bufor linii
    char *line = (char *)malloc(cols + 2);  // +2 na znak nowej linii i null-terminator
    if (line == NULL) {
        perror("Błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    MazeDim dims = {0, 0, -1, -1, -1, -1, -1, -1};
    dims.columns = cols; // Ustaw liczbę kolumn
    int y = 0;

    rewind(file); // Upewnij się, że czytanie zaczyna się od początku pliku

    while (fgets(line, cols + 2, file)) {
        int length = strlen(line);
        if (line[length - 1] == '\n') {
            line[length - 1] = '\0'; // Usuwa znak nowej linii
            length--;
        }

        for (int x = 0; x < length; x++) {
            if (line[x] == 'P' && dims.entryX == -1) { // Szuka 'P' tylko jeśli jeszcze nie znaleziono
                dims.entryX = x;
                dims.entryY = y;
                dims.start = y * dims.columns + x;
            } else if (line[x] == 'K' && dims.exitX == -1) { // Szuka 'K' tylko jeśli jeszcze nie znaleziono
                dims.exitX = x;
                dims.exitY = y;
                dims.end = y * dims.columns + x;
            }
        }
        y++; // Zwiększa liczbę wierszy
    }
    dims.rows = y;

    printf("Maze dimensions: %dx%d\n", dims.rows, dims.columns);
    printf("Entry: (%d, %d) Index: %d\n", dims.entryX, dims.entryY, dims.start);
    printf("Exit: (%d, %d) Index: %d\n", dims.exitX, dims.exitY, dims.end);

    free(line);  // Zwolnienie zaalokowanej pamięci
    return dims;
}


char readCell(FILE *file, int index, int col) {
    // Przesuwanie kursora pliku do odpowiedniego miejsca
    int k = index + (index / col); // Poprawka na nowe linie
    fseek(file, k, SEEK_SET); // +2 for newline and null terminator
    // Odczytanie i zwrócenie wartości komórki
    char x = fgetc(file);
    return x;
}

void writeCell(FILE *file, int index, int col, char character) {
    // Obliczamy indeks wiersza i kolumny na podstawie indeksu liniowego
    int k = index + (index / col); // Poprawka na nowe linie
    // Przesuwamy kursor pliku do odpowiedniego miejsca
    fseek(file, k, SEEK_SET);

    // Zapisujemy znak do pliku
    fputc(character, file);
}

void copyFile(FILE *sourceFile, FILE *destinationFile) {
    char ch;
    rewind(sourceFile);
    // Open the destination file in write mode
    // Copy contents character by character
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destinationFile);
    }
}

void restoreFile(FILE *file, char additionalChar) {
    rewind(file);
    char znak;
    while ((znak = fgetc(file)) != EOF) {
        if (znak != 'X' && znak != 'P' && znak != 'K' && znak != '\n' && znak != additionalChar) {
            fseek(file, -1, SEEK_CUR); // Przesuwa wskaźnik pliku o jeden bajt wstecz
            fputc(' ', file); // Zapisuje pusty znak w miejscu wystąpienia '-'
        }
    }
}


