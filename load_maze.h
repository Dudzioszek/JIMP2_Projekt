#include <stdio.h>
#ifndef LOAD_MAZE_H
#define LOAD_MAZE_H

#define MAX_SIZE 1024  // Maksymalny rozmiar labiryntu
#define MAZE_SIZE (MAX_SIZE * MAX_SIZE)  // Całkowita liczba komórek w labiryncie


typedef struct {
    int columns;      // Szerokość labiryntu
    int rows;        // Wysokość labiryntu
    int entryX;       // X-koordynat wejścia
    int entryY;       // Y-koordynat wejścia
    int start;   // Indeks liniowy wejścia
    int exitX;        // X-koordynat wyjścia
    int exitY;        // Y-koordynat wyjścia
    int end;    // Indeks liniowy wyjścia
} MazeDim;


extern MazeDim dims;


void initMazeDimensions(MazeDim *dims);
MazeDim analyzeMazeAndFindPositions(FILE *file);


void checkSize(FILE*, int*, int*);
void getData(FILE*, int, int*, int*);

char readCell(FILE*, int , int);
void writeCell(FILE*, int , int , char );
void copyFile(FILE *, FILE *);
void restoreFile(FILE*, char);

void checkSizeAndGetData(FILE *file, int *rows, int *cols, int *start, int *end);
#endif
