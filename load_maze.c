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

void getData(const char* filename, int cols, int* start, int* end) {

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
            if(line[temp_col] == 'K') {
                (*end) = index;
            }
            
            temp_col++;
        }
        temp_row++;
    }

    fclose(file);
    free(line); 
}

char readCell(const char *filename, int index, int col) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        return EOF; // Wartość EOF oznacza błąd odczytu
    }
    // Przesuwamy kursor pliku do odpowiedniego miejsca
    int k = index + (index/col); //biorę poprawkę na nowe linie
    fseek(file, k, SEEK_SET); // +2 for newline and null terminator
    // Odczytujemy i zwracamy wartość komórki
    // Zamykamy plik
    char x = fgetc(file);
    fclose(file);
    return x;
}


void writeCell(const char *filename, int index, int col, char character) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        return;
    }

    // Obliczamy indeks wiersza i kolumny na podstawie indeksu liniowego
    int k = index + (index / col); // biorę poprawkę na nowe linie

    // Przesuwamy kursor pliku do odpowiedniego miejsca
    fseek(file, k, SEEK_SET);

    // Zapisujemy znak do pliku
    fputc(character, file);

    // Zamykamy plik
    fclose(file);
}

void restoreFile(const char *nazwa_pliku) {
    FILE *plik_wejscie = fopen(nazwa_pliku, "r");
    FILE *plik_wyjscie = fopen("plik_wyjscie.txt", "w"); // Tworzymy nowy plik wyjściowy

    if (plik_wejscie == NULL || plik_wyjscie == NULL) {
        printf("Nie udało się otworzyć plików.\n");
        return;
    }

    char znak;
    while ((znak = fgetc(plik_wejscie)) != EOF) {
        if (znak == '-') {
            znak = ' ';
        }
        fputc(znak, plik_wyjscie);
    }

    fclose(plik_wejscie);
}
