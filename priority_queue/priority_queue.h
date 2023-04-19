#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct FibonacciHeap FibonacciHeap;

FibonacciHeap *heap_init(bool (*cmp)(void *, void *));

void insert(FibonacciHeap *heap, void *data, size_t size_data);

void extract(FibonacciHeap *heap);

void *get_top(FibonacciHeap *heap);

void clear_heap(FibonacciHeap *heap);

typedef struct PriorityQueue PriorityQueue;

PriorityQueue *priority_queue_init(bool (*cmp)(void *, void *));

void push(PriorityQueue *queue, void *data, size_t size_data);

void *top(PriorityQueue *queue);

int size(PriorityQueue *queue);

void pop(PriorityQueue *queue);

bool empty(PriorityQueue *queue);

void clear_priority_queue(PriorityQueue *queue);

#endif //PRIORITY_QUEUE_H
