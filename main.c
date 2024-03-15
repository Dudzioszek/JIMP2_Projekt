#include "load_maze.h"
#include "char_stack.h"
#include "int_stack.h"
#include "short_stack.h"
#include "algorytm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IN "maze.txt"
#define OUT "kroki.txt"

void dodajSciezke(FILE *file, CharStack *moves, int start, int col) {
    int cell = start;
    int i = 0;
    char move;
    while(i <= moves->index) {       
        move = moves->array[i];
        writeCell(file, cell, col, '-');
        switch(move) {
                case 'N':
                    cell -= col;
                    break;
                case 'S':
                    cell += col;
                    break;
                case 'E':
                    cell += 1;
                    break;
                case 'W':
                    cell -= 1;
                    break;
            }
        i++;
        }
}

int main() {
    int rows = 0, cols = 0, start = 0, end = 0;
    // przechowuje dlugosc drogi od węzła do węzła
    short int currPathLen = 0;
    //zawiera priorytet kierunków, np: ESWN - prawo-dół-lewo-góra
    char directions[5];
    FILE *maze = fopen(IN, "r+");
    //komórka którą algorytm wybierze jako następną
    int nextCell;
    //liczba możliwości ruchu
    int routesCount = 1;

    //inicjalizuje stosy
    CharStack *allMoves = initCharStack();
    IntStack *nodes = initInt();
    MiniIntStack *pathLens = initMiniInt();

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
    //ustalam priorytet poruszania sie
    makePrio(directions, rows, cols, end);
    printf("Priorytety kierunkow: %.4s\n", directions);
    
    char currMove = firstMove(maze, &currCell, cols, mazeSize);

    printf("Pierwszy ruch: %c\n", currMove);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    writeCell(maze, currCell, cols, '-');
    writeCell(maze, start, cols, '-');
    //Usuwam tymczasowo K z mapy aby algorytm traktował je jako przestrzeń
    writeCell(maze, end, cols, ' ');
    currPathLen++;

    //dodaje ruch na stos
    pushChar(allMoves, currMove);

    printf("Rozpoczynam algorytm...\n");

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, directions, &nextCell, currCell, &routesCount, cols);
        switch(routesCount) {
            case 0:
                currCell = removeInt(nodes);
                removeMultiChar(allMoves, currPathLen);
                currPathLen = removeMiniInt(pathLens);
                break;
            case 1:
                pushChar(allMoves, currMove);
                currCell = nextCell;
                writeCell(maze, currCell, cols, '-');
                currPathLen++;
                break;
            default:
                pushInt(nodes, currCell);
                pushMiniInt(pathLens, currPathLen);
                currPathLen = 1;
                currCell = nextCell;
                writeCell(maze, currCell, cols, '-');
                pushChar(allMoves, currMove);
                break;
        }
    }
    
    //Po włączeniu plik będzie zawierał ścieżkę wyjściową
    /*
        restoreFile(maze);
        dodajSciezke(maze, allMoves, start, cols);
    */

    //Zwalniam pamięć
    freeMiniInt(pathLens);
    freeInt(nodes);

    
    int movesCount = PrintMoves(allMoves, OUT);
    printf("Rozwiazanie sklada sie z %d ruchow\n", movesCount);
   
    freeChar(allMoves);
    
    //Wypełniam P i K aby można było wyczyścić dawną ścieżkę
    writeCell(maze, start, cols, 'P');
    writeCell(maze, end, cols, 'K');
    //Usuwam z pliku ścieżkę
    restoreFile(maze);
    fclose(maze);

    return 0;
}