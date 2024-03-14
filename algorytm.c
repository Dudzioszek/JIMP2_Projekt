#include "algorytm.h"
#include "load_maze.h"
#include <stdio.h>

//wybieram priorytet ruchów
void makePrio(char *directions, int rows, int cols, int end) {
    //transformacja współrzędnej liniowej na dwa wymiary
    int x = (end % cols) + 1;
    int y = (end / cols) + 1;

    //jeśli preferowany kierunek to VERTICAL, jako pierwszy wybieram kierunek pionowy
    if (DIR_PREF == 'V') {
        directions[0] = y >= rows / 2 ? 'S' : 'N';
        directions[1] = x >= cols / 2 ? 'E' : 'W';
    } else { // Zakładam że DIR_PREF == 'H'
        directions[0] = x >= cols / 2 ? 'E' : 'W';
        directions[1] = y >= rows / 2 ? 'S' : 'N';
    }

    // W drugim przypadku wyniki są poprostu zamieniane
    directions[2] = directions[0] == 'S' ? 'N' : (directions[0] == 'N' ? 'S' : (directions[0] == 'E' ? 'W' : 'E'));
    directions[3] = directions[1] == 'E' ? 'W' : (directions[1] == 'W' ? 'E' : (directions[1] == 'S' ? 'N' : 'S'));

    directions[4] = '\0';
}

//funkcja wykonująca pierwszy ruch
char firstMove(const char* fileName, int *cell, int cols, int size) {
    if(*cell - cols < 0) {
        (*cell) += cols;
        return 'S';
    }

    if((*cell) + cols >= size) {
        (*cell) -= cols;
        return 'N';
    }
    
    if(readCell(fileName, (*cell)-cols, cols) == ' ') {
            (*cell)-= cols;
            return 'N';
        }

    if(readCell(fileName, (*cell)+cols, cols) == ' ') {
            (*cell)+= cols;
            return 'S';
        }

    if(readCell(fileName, (*cell)-1, cols) == ' ') {
            (*cell) -= 1;
            return 'W';
        }

    if(readCell(fileName, (*cell)+1, cols) == ' ') {
            (*cell) += 1;
            return 'E';
        }

    return 'X';
}

//główna funkcja wykonująca ruch
char move(const char* fileName, char *directions, int* new_cell, int cell, int *count, int col) {
    //ta zmienna inforumuje ile jest opcji ruchu w tej komorce
    int j = 0;
    //Kolejne przypadki N,S,E,W
    int opt[4] = {cell - col, cell + col, cell + 1, cell - 1};
    //jeśli brak ruchu to zwraca X
    char move = 'X';

    for(int i = 3; i >= 0; i--) {
        switch(directions[i]) {
            case 'N':
                if(readCell(fileName, opt[0], col) == ' ') {
                    *new_cell = opt[0];
                    move = 'N';
                    j++;
                }
                break;
            case 'S':
                if(readCell(fileName, opt[1], col) == ' ') {
                    *new_cell = opt[1];
                    move = 'S';
                    j++;
                }
                break;
            case 'E':
                if(readCell(fileName, opt[2], col) == ' ') {
                    *new_cell = opt[2];
                    move = 'E';
                    j++;
                }
                break;
            case 'W':
                if(readCell(fileName, opt[3], col) == ' ') {
                    *new_cell = opt[3];
                    move = 'W';
                    j++;
                }
                break;
        }
    }

    //w "new_cell" zostanie zapisana ostatnia (najnowsza) komórka
    //tak samo "move"
    //jeśli komórka jest dostępna to j++

    //count zawiera liczbę dostępnych komórek
    (*count) = j;

    //zwracam jaki ruch wykona algorytm
    return move;
}