#ifndef LOAD_MAZE_H
#define LOAD_MAZE_H

#define MAX_SIZE 1024  // Maksymalny rozmiar labiryntu
#define MAZE_SIZE (MAX_SIZE * MAX_SIZE)  // Całkowita liczba komórek w labiryncie

void checkSize(const char*, int*, int*);
void getData(const char*, char*, int*, int* , int*, int*);

#endif
