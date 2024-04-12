#include "bfs.h"
#include "load_maze.h"
#include "queue.h"
#include <stdio.h>


#define OUT_DIR "output/"
#define OUT OUT_DIR "kroki.txt"


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


void runBFS(FILE* maze) {


    // Inicjalizacja zmiennych
    int rows = 0, cols = 0, start = 0, end = 0;

    FILE *temp = fopen("temp.txt", "w+");


    //liczba możliwości ruchu
    int routesCount = 1;

    //inicjalizuje kolejkę
    Queue* queue = initializeQueue(temp);


    //pobieram z pliku rozmiar labiryntu
    checkSizeAndGetData(maze, &rows, &cols, &start, &end);

    int mazeSize = rows*cols;


    //obecna komórka
    int currCell = start;
    
    char currMove = firstMoveb(maze, &currCell, cols, mazeSize);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    //writeCell(maze, currCell, cols, '-');
    writeCell(maze, start, cols, '-');
    //Usuwam tymczasowo K z mapy aby algorytm traktował je jako przestrzeń
    writeCell(maze, end, cols, ' ');

    printf("Rozpoczynam algorytm BFS...\n");

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = moveb(maze, queue, &routesCount, currCell, cols);
        writeCell(maze, currCell, cols, '-');
        if(routesCount > 1) {
            writeCell(maze, currCell, cols, currMove);
        }
        currCell = pop(queue);
    }
    

    //Zwalniam pamięć
    deleteQueue(queue);
    int counter = printMovesq(maze, OUT, start, end, cols);
    printf("Znaleziono sciezke od dlugosci: %d krokow\n", counter);
    //Usuwam znaki wypisane przez algorytm
    restoreFile(maze);
    //Wypełniam P i K
    writeCell(maze, start, cols, 'P');
    writeCell(maze, end, cols, 'K');
    //Usuwam z pliku ścieżkę
    fclose(maze);
    fclose(temp);
    remove("temp.txt");
}