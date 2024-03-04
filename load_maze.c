#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>

void checkSize(const char* filename, int* rows, int* cols) {
    // Otwarcie pliku
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        exit(EXIT_FAILURE);
    }

    //zczytuje liczbe kolumn
    while (getc(file) != '\n') {
        (*cols)++;
    }

    //tworze zmienna pomocnicza line
    char *line = (char*)malloc((*cols) * sizeof(char) + 1); // Allocate memory for the line
    if (line == NULL) {
        perror("Błąd alokacji pamięci");
        exit(EXIT_FAILURE);
    }

    //zczytuje liczbe wierszy
    (*rows)++;
    while (fgets(line, (*cols) + 2, file) != NULL) {
        (*rows)++;
    }

    fclose(file);
    //zwalniam pamiec po line
    free(line); 

}

void getData(const char* filename, char *maze, int cols, int* start, int* end) {

    // Otwarcie pliku
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        exit(EXIT_FAILURE);
    }

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
            if(line[temp_col] == 'K') (*end) = index;
            
            maze[index] = line[temp_col];
            temp_col++;
        }
        temp_row++;
    }

    fclose(file);
    free(line); 
}
