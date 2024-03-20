#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

Node* createNode(int data);
Queue* initializeQueue();
void push(Queue* queue, int data);
int pop(Queue* queue);
void deleteQueue(Queue* queue);
void printMoves(FILE *, const char*, int, int, int);

#endif /* QUEUE_H */