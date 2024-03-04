#include "load_maze.h"
#include <stdio.h>
#include <stdlib.h>

#define PLIK "maze.txt"

//ta funkcja to jedynie podglad dzialania alokacji,
//jest niepotrzebna do dzialania programu
void printMaze(char *maze, int cols, int mazeSize);

int main() {
    int rows = 0, cols = 0, start = 0, end = 0;;

    //pobieram z pliku rozmiar labiryntu
    checkSize(PLIK, &rows, &cols);
    int mazeSize = rows*cols;

    //ta zmienna przechowuje sciany oraz przestrzen labiryntu
    char *maze = calloc(mazeSize, sizeof(char));

    //zapelniam zmienna maze, start i end
    getData(PLIK, maze, cols, &start, &end);

    printf("Rozmiar labiryntu: %d x %d\nwspolrzedna wejscia: %d\nwspolrzedna wyjscia: %d\n", rows, cols, start, end);
    printf("Rozmiar zmiennej maze: %ld\n", sizeof(maze));
    //wypisuje labirynt
    //printMaze(maze, cols, mazeSize);

    free(maze);

    return 0;
}


void printMaze(char *maze, int cols, int mazeSize) {
    int i = 0;
    while(i < mazeSize) {
        printf("%c", maze[i]);
        //dodaje nowa linie w wypisaniu (niepotrzebne)
        if((i+1)%cols == 0) printf("\n");
        i++;
    }
}