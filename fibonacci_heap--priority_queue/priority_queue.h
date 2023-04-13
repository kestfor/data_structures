#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>

typedef struct PriorityQueue PriorityQueue;

PriorityQueue *priority_queue_init(void);

void push(PriorityQueue *queue, int data);

int top(PriorityQueue *queue);

int size(PriorityQueue *queue);

int pop(PriorityQueue *queue);

bool empty(PriorityQueue *queue);

void clear_priority_queue(PriorityQueue *queue);

#endif //PRIORITY_QUEUE_H
