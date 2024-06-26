#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>

typedef struct Queue {
    int front;
    int rear;
    FILE *file;
} Queue;

Queue* initializeQueue();
void push(Queue* queue, int data);
int pop(Queue* queue);
void deleteQueue(Queue* queue);
int printMovesq(FILE *, const char*, int, int, int);
void translateSteps(const char *, const char *, int);

#endif /* QUEUE_H */