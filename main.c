#include "load_maze.h"
#include "algorytm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

#define IN "maze.txt"
#define OUT "kroki.txt"

int main() {
    int rows = 0, cols = 0, start = 0, end = 0;
    //zawiera priorytet kierunków, np: ESWN - prawo-dół-lewo-góra
    FILE *maze = fopen(IN, "r+");
    FILE *temp = fopen("temp.txt", "w+");

    //liczba możliwości ruchu
    int routesCount = 1;

    //inicjalizuje kolejkę
    Queue* queue = initializeQueue(temp);


    //pobieram z pliku rozmiar labiryntu
    checkSizeAndGetData(maze, &rows, &cols, &start, &end);

    int mazeSize = rows*cols;

    //ta zmienna przechowuje sciany oraz przestrzen labiryntu

    
    //jesli nie zostanie wczytany początek lub koniec to nie ma roz.
    if(start == 0 || end == 0) {
        printf("Nie znaleziono poczatku lub konca labiryntu\n");
        return -1;
    }

    //obecna komórka
    int currCell = start;
    
    char currMove = firstMove(maze, &currCell, cols, mazeSize);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    //writeCell(maze, currCell, cols, '-');
    writeCell(maze, start, cols, '-');
    //Usuwam tymczasowo K z mapy aby algorytm traktował je jako przestrzeń
    writeCell(maze, end, cols, ' ');

    printf("Rozpoczynam algorytm...\n");

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, queue, &routesCount, currCell, cols);
        writeCell(maze, currCell, cols, '-');
        if(routesCount > 1) {
            writeCell(maze, currCell, cols, currMove);
        }
        currCell = pop(queue);
    }
    

    //Zwalniam pamięć
    deleteQueue(queue);
    int counter = printMoves(maze, OUT, start, end, cols);
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

    return 0;
}