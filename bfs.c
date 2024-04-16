#include "bfs.h"
#include "load_maze.h"
#include "queue.h"
#include <stdio.h>

#define OUT_DIR "output/"
#define OUT OUT_DIR "kroki.txt"
#define OUTPATHFILE "output/labiryntZeSciezka.txt"

//funkcja wykonująca pierwszy ruch
char firstMoveb(FILE *file, int *cell, int cols, int size) {
    if (*cell - cols < 0) {
        (*cell) += cols;
        return 'S';
    }

    if ((*cell) + cols >= size) {
        (*cell) -= cols;
        return 'N';
    }

    if (readCell(file, (*cell) - cols, cols) == ' ') {
        (*cell) -= cols;
        return 'N';
    }

    if (readCell(file, (*cell) + cols, cols) == ' ') {
        (*cell) += cols;
        return 'S';
    }

    if (readCell(file, (*cell) - 1, cols) == ' ') {
        (*cell) -= 1;
        return 'W';
    }

    if (readCell(file, (*cell) + 1, cols) == ' ') {
        (*cell) += 1;
        return 'E';
    }

    return 'X';
}


char moveb(FILE *file, Queue *queue, int *routesPossible, int cell, int col) {
    // Ta zmienna informuje ile jest opcji ruchu w tej komórce
    (*routesPossible) = 0;
    // Kolejne przypadki N,S,E,W
    int opt[4] = {cell - col, cell + col, cell + 1, cell - 1};
    // Jeśli brak ruchu to zwraca X
    char *moves = "NSEW";
    char move = 'X';

    for (int i = 0; i <= 3; i++) {
        if (readCell(file, opt[i], col) == ' ') {
            push(queue, opt[i]);
            (*routesPossible)++;
            }
        else if (readCell(file, opt[i], col) == '-') {
            move = moves[i];
        }
    }

    return move;
}


int runBFS(FILE* maze,MazeDim dims) {

    

    FILE *temp = fopen("temp.txt", "w+");


    //liczba możliwości ruchu
    int routesCount = 1;

    //inicjalizuje kolejkę
    Queue* queue = initializeQueue(temp);


    //pobieram z pliku rozmiar labiryntu

    int mazeSize = dims.rows*dims.columns;


    //obecna komórka
    int currCell = dims.start;
    
    char currMove = firstMoveb(maze, &currCell, dims.columns, mazeSize);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    //writeCell(maze, currCell, cols, '-');
    writeCell(maze, dims.start, dims.columns, '-');
    //Usuwam tymczasowo K z mapy aby algorytm traktował je jako przestrzeń
    writeCell(maze, dims.end, dims.columns, ' ');

    printf("Rozpoczynam algorytm BFS...\n");

    while(currCell != dims.end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = moveb(maze, queue, &routesCount, currCell, dims.columns);
        writeCell(maze, currCell, dims.columns, '-');
        if(routesCount > 1) {
            writeCell(maze, currCell, dims.columns, currMove);
        }
        currCell = pop(queue);
    }
    

    //Zwalniam pamięć
    deleteQueue(queue);
    int counter = printMovesq(maze, "output/krokiTemp.txt", dims.start, dims.end, dims.columns);
    translateSteps("output/krokiTemp.txt",  OUT, counter);
    printf("Znaleziono sciezke od dlugosci: %d\n", counter);
    //Usuwam znaki wypisane przez algorytm
    restoreFile(maze, '*');
    FILE* outWithPath = fopen(OUTPATHFILE, "w+");
    copyFile(maze, outWithPath);
    restoreFile(maze, '-');
    //Wypełniam P i K w maze
    writeCell(maze, dims.start, dims.columns, 'P');
    writeCell(maze, dims.end, dims.columns, 'K');
    //Wypełniam P i K w outWithPath
    writeCell(outWithPath, dims.start, dims.columns, 'P');
    writeCell(outWithPath, dims.end, dims.columns, 'K');
    //Usuwam z pliku ścieżkę
    fclose(maze);
    fclose(temp);
    fclose(outWithPath);
    remove("output/krokiTemp.txt");


    return counter;
}