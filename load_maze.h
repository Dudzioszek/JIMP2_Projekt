#ifndef LOAD_MAZE_H
#define LOAD_MAZE_H

#define MAX_SIZE 1024  // Maksymalny rozmiar labiryntu
#define MAZE_SIZE (MAX_SIZE * MAX_SIZE)  // Całkowita liczba komórek w labiryncie

void loadMaze(const char* filename, char maze[MAZE_SIZE], int* rows, int* cols);
void printMaze(const char maze[MAZE_SIZE], int rows, int cols);

#endif
