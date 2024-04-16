#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void initMazeDimensions(MazeDim *dims) {
    dims->columns = 0;        // Liczba kolumn jest początkowo 0.
    dims->rows = 0;          // Liczba linii jest początkowo 0.
    dims->entryX = -1;        // X-koordynat wejścia nieznany.
    dims->entryY = -1;        // Y-koordynat wejścia nieznany.
    dims->start= -1;    // Indeks liniowy wejścia nieznany.
    dims->exitX = -1;         // X-koordynat wyjścia nieznany.
    dims->exitY = -1;         // Y-koordynat wyjścia nieznany.
    dims->end = -1;     // Indeks liniowy wyjścia nieznany.
}


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




// void checkSizeAndGetData(FILE *file, int *rows, int *cols, int *start, int *end) {
//     *cols = 0;
//     int ch;

//     // Zczytywanie liczby kolumn do pierwszego znaku nowej linii
//     while ((ch = getc(file)) != '\n' && ch != EOF) {
//         (*cols)++;
//     }

//     if (*cols == 0) {
//         perror("Plik jest pusty lub błąd przy czytaniu pierwszej linii");
//         exit(EXIT_FAILURE);
//     }

//     char *line = (char *)malloc((*cols) + 2);
//     if (line == NULL) {
//         perror("Błąd alokacji pamięci");
//         exit(EXIT_FAILURE);
//     }

//     *rows = 1; // Zainicjalizuj rows jako 1, ponieważ mamy już pierwszą linię
//     rewind(file); // Upewnij się, że czytanie zaczyna się od początku pliku

//     *start = *end = -1; // Inicjalizacja start i end jako -1, aby oznaczyć nieznalezienie
//     int temp_row = 0;

//     while (fgets(line, (*cols) + 2, file) != NULL) {
//         if (temp_row > 0) { // Liczenie wierszy zaczyna się od drugiego, ponieważ pierwszy już mamy
//             (*rows)++;
//         }
//         for (int temp_col = 0; temp_col < *cols; temp_col++) {
//             int index = temp_row * (*cols) + temp_col; // Obliczenie indeksu

//             if (line[temp_col] == 'P' && *start == -1) *start = index; // Ustaw start, jeśli to pierwsze 'P'
//             else if (line[temp_col] == 'K' && *end == -1) *end = index; // Ustaw end, jeśli to pierwsze 'K'
//         }
//         temp_row++;
//     }

//     printf("Wczytano labirynt o wymiarach %dx%d\n", *rows, *cols);
//     printf("Start: %d, End: %d\n", *start, *end);

//     if (*start == -1 || *end == -1) {
//         fprintf(stderr, "Nie znaleziono P lub K w pliku\n");
//         exit(EXIT_FAILURE);
//     }

//     //printuj


//     free(line);
// }

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


