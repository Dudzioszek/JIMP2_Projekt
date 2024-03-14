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

int main() {
    int rows = 0, cols = 0, start = 0, end = 0;
    // przechowuje dlugosc drogi od węzła do węzła
    short int currPathLen = 0;
    //zawiera priorytet kierunków, np: ESWN - prawo-dół-lewo-góra
    char directions[5];
    
    //komórka którą algorytm wybierze jako następną
    int nextCell;
    //liczba możliwości ruchu
    int routesCount = 1;

    //inicjalizuje stosy
    CharStack *allMoves = createCharStack();
    Stack *nodes = createStack();
    ShortStack *pathLens = createShortStack();

    //pobieram z pliku rozmiar labiryntu
    checkSize(IN, &rows, &cols);

    int mazeSize = rows*cols;

    //ta zmienna przechowuje sciany oraz przestrzen labiryntu
    //char *maze = calloc(mazeSize, sizeof(char));

    //zapelniam zmienna maze, start i end
    getData(IN, cols, &start, &end);

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
    
    char currMove = firstMove(IN, &currCell, cols, mazeSize);

    printf("Pierwszy ruch: %c\n", currMove);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na '-'
    writeCell(IN, currCell, cols, '-');
    writeCell(IN, start, cols, '-');
    writeCell(IN, end, cols, ' ');
    currPathLen++;

    //dodaje ruch na stos
    pushChar(allMoves, currMove);

    printf("Rozpoczynam algorytm\n");

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(IN, directions, &nextCell, currCell, &routesCount, cols);
        switch(routesCount) {
            case 0:
                currCell = pop(nodes);
                popCharMultiple(allMoves, currPathLen);
                currPathLen = popShort(pathLens);
                break;
            case 1:
                pushChar(allMoves, currMove);
                currCell = nextCell;
                writeCell(IN, currCell, cols, '-');
                currPathLen++;
                break;
            default:
                push(nodes, currCell);
                pushShort(pathLens, currPathLen);
                currPathLen = 1;
                currCell = nextCell;
                writeCell(IN, currCell, cols, '-');
                pushChar(allMoves, currMove);
                break;
        }
    }

    writeCell(IN, start, cols, 'P');
    writeCell(IN, end, cols, 'K');
    //restoreFile(IN);
    deleteStack(nodes);
    deleteShortStack(pathLens);
    reverseCharStack(allMoves);
    int k = printMoves(allMoves, OUT);
    printf("Rozwiazanie sklada sie z %d ruchow\n", k);
    deleteCharStack(allMoves);

    return 0;
}