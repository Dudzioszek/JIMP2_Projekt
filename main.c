#include "load_maze.h"
#include <stdio.h>

int main() {
    char maze[MAZE_SIZE];  // Tablica jednowymiarowa na labirynt
    int rows = 0, cols = 0;

    
    loadMaze("maze.txt", maze, &rows, &cols);
    printMaze(maze, rows, cols);
    printf("Rozmiar labiryntu: %d x %d\n", rows, cols);

    return 0;
}
