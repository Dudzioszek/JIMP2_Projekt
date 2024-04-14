#include <stdio.h>
#include <string.h>
#ifndef LOAD_MAZE_H
#define LOAD_MAZE_H

#define MAX_SIZE 1024  // Maksymalny rozmiar labiryntu
#define MAZE_SIZE (MAX_SIZE * MAX_SIZE)  // Całkowita liczba komórek w labiryncie

void checkSize(FILE*, int*, int*);
void getData(FILE*, int, int*, int*);

char readCell(FILE*, int , int);
void writeCell(FILE*, int , int , char );
void restoreFile(FILE*);

void checkSizeAndGetData(FILE *file, int *rows, int *cols, int *start, int *end);

typedef struct {
    int columns;      // Width of the maze
    int lines;        // Height of the maze
    int entryX;       // X-coordinate of the entry
    int entryY;       // Y-coordinate of the entry
    int exitX;        // X-coordinate of the exit
    int exitY;        // Y-coordinate of the exit
} MazeDimensions;

MazeDimensions analyzeMaze(const char* textFilePath);

#endif
