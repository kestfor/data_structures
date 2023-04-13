#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <stdbool.h>

typedef struct FibonacciHeap FibonacciHeap;

FibonacciHeap *heap_init(void);

void insert(FibonacciHeap *heap, int value);

int extract_min(FibonacciHeap *heap);

int get_min(FibonacciHeap *heap);

void clear_heap(FibonacciHeap *heap);

#endif //FIBONACCI_HEAP_H
