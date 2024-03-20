#define DIR_PREF 'H' //albo V - vertical, H - horizontal
#include <stdio.h>
#include "queue.h"

void makePrio(char *, int, int, int);
char firstMove(FILE*, int *, int, int);
char move(FILE*, Queue *, int*, int, int);