#include <stdio.h>
#ifndef LOAD_MAZE_H
#define LOAD_MAZE_H

#define MAX_SIZE 1024  // Maksymalny rozmiar labiryntu
#define MAZE_SIZE (MAX_SIZE * MAX_SIZE)  // Całkowita liczba komórek w labiryncie

void checkSize(FILE*, int*, int*);
void getData(FILE*, int, int*, int*);

char readCell(FILE*, int , int);
void writeCell(FILE*, int , int , char );
void copyFile(FILE *, FILE *);
void restoreFile(FILE*, char);

void checkSizeAndGetData(FILE *file, int *rows, int *cols, int *start, int *end);
#endif
