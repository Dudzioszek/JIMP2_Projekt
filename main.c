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
    char *maze = calloc(mazeSize, sizeof(char));

    //zapelniam zmienna maze, start i end
    getData(IN, maze, cols, &start, &end);

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
    maze[currCell] = '-';
    maze[start] = '-';
    currPathLen++;

    //dodaje ruch na stos
    pushChar(allMoves, currMove);

    printf("Rozpoczynam algorytm");

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, directions, &nextCell, currCell, &routesCount, cols); 
        switch(routesCount) {
            case 0: // nie ma możliwości ruchu
                currCell = pop(nodes); // cofanie się do poprzedniego węzła
                popCharMultiple(allMoves, currPathLen); // usuwanie z stosu ruchy z poprzedniego węzła
                currPathLen = popShort(pathLens); // pobranie długości drogi do poprzedniego węzła
                break;
            case 1: // jest tylko jedna możliwość ruchu
                pushChar(allMoves, currMove);
                currCell = nextCell; // przechodzenie do następnego węzła
                maze[currCell] = '-'; // oznaczanie jako odwiedzony
                currPathLen++; 
                break;
            default: // jest więcej niż jedna możliwość ruchu
                push(nodes, currCell); // zapisanie obecnego węzła na stos
                pushShort(pathLens, currPathLen); // zapisanie długości drogi do węzła
                currPathLen = 1;
                currCell = nextCell;
                maze[currCell] = '-'; 
                pushChar(allMoves, currMove); // zapisanie ruchu na stos
                break;
        }
    }

    free(maze);
    deleteStack(nodes);
    deleteShortStack(pathLens);
    int k = printMoves(allMoves, OUT);
    printf("Rozwiazanie sklada sie z %d ruchow\n", k);
    deleteCharStack(allMoves);

    return 0;
}