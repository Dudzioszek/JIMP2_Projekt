#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>

void checkSize(FILE *file, int *rows, int *cols) {
    // Zczytywanie liczby kolumn
    while (getc(file) != '\n') {
        (*cols)++;
    }

    // Tworzenie zmiennej pomocniczej line
    char *line = (char *)malloc((*cols) * sizeof(char) + 1); // Alokacja pamięci na linię
    if (line == NULL) {
        perror("Błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    // Zczytywanie liczby wierszy
    (*rows)++;
    while (fgets(line, (*cols) + 2, file) != NULL) {
        (*rows)++;
    }

    // Zwalnianie pamięci po line
    free(line);
}


void getData(FILE *file, int cols, int *start, int *end) {
    // Otwarcie pliku
    if (file == NULL) {
        perror("Nie można otworzyć pliku lub znaleźć pliku z labiryntem");
        exit(EXIT_FAILURE);
    }
    rewind(file);

    //tworze zmienna pomocnicza line
    char *line = (char*)malloc(cols * sizeof(char) + 1); // Allocate memory for the line
    if (line == NULL) {
        perror("Błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    //tymczasowa kolumna i rzad
    int temp_col, temp_row = 0, index;

    //zapisuje w zmiennej maze kolejne elementy labiryntu
    while (fgets(line, cols + 2, file)) {
        temp_col = 0;
        while (temp_col < cols) {
            index = temp_row * cols + temp_col;  // Obliczenie indeksu w tablicy jednowymiarowej

            //jesli znajde P lub K to zapisuje w start lub end
            if(line[temp_col] == 'P') (*start) = index;
            if(line[temp_col] == 'K') {
                (*end) = index;
            }
            
            temp_col++;
        }
        temp_row++;
    }
    free(line); 
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


void restoreFile(FILE *file) {
    if (file == NULL) {
        printf("Nie udało się otworzyć pliku.\n");
        return;
    }
    rewind(file);
    char znak;
    while ((znak = fgetc(file)) != EOF) {
        if (znak == '-') {
            fseek(file, -1, SEEK_CUR); // Przesuwa wskaźnik pliku o jeden bajt wstecz
            fputc(' ', file); // Zapisuje pusty znak w miejscu wystąpienia '-'
        }
    }
}

