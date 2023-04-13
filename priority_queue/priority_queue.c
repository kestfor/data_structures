#include <stdlib.h>
#include <stdbool.h>
#include "fibonacci_heap.h"

typedef struct {
    FibonacciHeap *heap;
    int size;
} PriorityQueue;

PriorityQueue *priority_queue_init(void) {
    PriorityQueue *new = malloc(sizeof(PriorityQueue));
    new->heap = heap_init();
    new->size = 0;
    return new;
}

void push(PriorityQueue *queue, int data) {
    insert(queue->heap, data);
    queue->size++;
}

int top(PriorityQueue *queue) {
    return get_min(queue->heap);
}

int size(PriorityQueue *queue) {
    return queue->size;
}

int pop(PriorityQueue *queue) {
    return extract_min(queue->heap);
}

bool empty(PriorityQueue *queue) {
    return queue->size == 0;
}

void clear_priority_queue(PriorityQueue *queue) {
    clear_heap(queue->heap);
    free(queue);
}