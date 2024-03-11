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
        printf("Labirynt nie ma rozwiązania!!\n");
        return -1;
    }

    //obecna komórka
    int currCell = start;
    
    //ustalam priorytet poruszania sie
    makePrio(directions, rows, cols, end);
    printf("Priorytety kierunkow: %.4s\n", directions);
    
    char currMove = firstMove(maze, &currCell, cols, mazeSize);
    
    //kiedy program odwiedzi komórkę to zmienia ją z ' ' na 'V'
    maze[currCell] = 'V';
    currPathLen++;

    //dodaje ruch na stos
    pushChar(allMoves, currMove);

    bool isNode = false;

    while(currCell != end) {
        //zbieram dane tj.: możliwe ruchy, ich liczba, współrzędne każdego z nich
        currMove = move(maze, directions, &nextCell, currCell, &routesCount, cols);
        switch(routesCount) {
            case 0:
                //jeśli brak ruchów w węźle
                if(isNode == true) {
                    currCell = pop(nodes);
                    printf("przed: %d\n", currPathLen);
                    currPathLen = popShort(pathLens);
                    //usuwam tyle ruchów, ile wynosi długość obecnej ścieżki
                    popCharMultiple(allMoves, currPathLen);
                }
                else {
                    //jeśli brak ruchów na końcu ścieżki
                    printf("przed: %d\n", currPathLen);
                    popCharMultiple(allMoves, currPathLen);
                    currPathLen = 0;
                    currCell = pop(nodes);
                    isNode = true;
                }
                break;
            case 1:
                isNode = false;
                pushChar(allMoves, currMove);
                currCell = nextCell;
                maze[currCell] = 'V';
                currPathLen++;
                break;
            default:
                isNode = false;
                push(nodes, currCell);
                pushShort(pathLens, currPathLen);
                currPathLen = 1;
                currCell = nextCell;
                maze[currCell] = 'V';
                pushChar(allMoves, currMove);
                break;
        }
    }

    free(maze);
    deleteStack(nodes);
    deleteShortStack(pathLens);

    printMoves(allMoves, OUT);
    deleteCharStack(allMoves);

    return 0;
}