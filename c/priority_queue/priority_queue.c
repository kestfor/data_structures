#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_AMOUNT_ROOTS 64

static struct Node {
    struct Node *child;
    struct Node *left;
    struct Node *right;
    void *data;
    int rank;
} Node;

typedef struct FibonacciHeap {
    struct Node *min;
    bool (*cmp) (void *, void*);
} FibonacciHeap;

struct Node *node_init(void *data, size_t size_data) {
    struct Node *new_node = malloc(sizeof(struct Node));
    *new_node = (struct Node) {NULL, NULL, NULL, NULL, 0};
    new_node->data = malloc(size_data);
    memcpy(new_node->data, data, size_data);
    return new_node;
}

FibonacciHeap *heap_init(bool (*cmp) (void *, void *)) {
    FibonacciHeap *new_heap = malloc(sizeof(FibonacciHeap));
    new_heap->min = NULL;
    new_heap->cmp = cmp;
    return new_heap;
}


void insert(FibonacciHeap *heap, void *data, size_t size_data) {
    struct Node *new_node = node_init(data, size_data);
    if (heap->min == NULL) {
        heap->min = new_node;
        new_node->left = new_node;
        new_node->right = new_node;
    } else {
        new_node->left = heap->min;
        new_node->right = heap->min->right;
        heap->min->right = new_node;
        new_node->right->left = new_node;
    }
    if (heap->cmp(data, heap->min->data)) {
        heap->min = new_node;
    }
}

void union_roots(struct Node *first_root, struct Node *second_root) {
    if (first_root == NULL || second_root == NULL || first_root == second_root) {
        return;
    }
    struct Node *tmp1 = first_root->right;
    struct Node *tmp2 = second_root->left;
    first_root->right = second_root;
    second_root->left = first_root;
    tmp2->right = tmp1;
    tmp1->left = tmp2;
}

struct Node *merge(struct Node *first, struct Node *second, bool (*cmp)(void *, void *)) {
    if (cmp(first->data, second->data)) {
        second->right = second;
        second->left = second;
        if (first->child == NULL) {
            first->child = second;
        } else {
            union_roots(first->child, second);
        }
        first->rank++;
        return first;
    } else {
        first->right = first;
        first->left = first;
        if (second->child == NULL) {
            second->child = first;
        } else {
            union_roots(first, second->child);
        }
        second->rank++;
        return second;
    }
}

void consolidate(FibonacciHeap *heap) {
    struct Node *curr_node = heap->min;
    struct Node *min = heap->min;
    struct Node *used[MAX_AMOUNT_ROOTS] = {NULL};
    while (true) {
        struct Node *next = curr_node->right;
        int rank = curr_node->rank;
        if (used[rank] == NULL) {
            used[rank] = curr_node;
        } else {
            while (true) {
                curr_node = merge(curr_node, used[rank], heap->cmp);
                curr_node->left = curr_node;
                curr_node->right = curr_node;
                used[rank] = NULL;
                rank++;
                if (used[rank] == NULL) {
                    used[rank] = curr_node;
                    break;
                }
            }
        }
        curr_node = next;
        if (curr_node == heap->min) {
            break;
        }
    }
    struct Node *first = NULL;
    struct Node *prev = NULL;
    for (int i = 0; i < MAX_AMOUNT_ROOTS; i++) {
        if (used[i] != NULL) {
            if (!heap->cmp(min->data, used[i]->data)) {
                min = used[i];
            }
            if (prev == NULL) {
                prev = used[i];
                first = used[i];
            } else {
                prev->right = used[i];
                used[i]->left = prev;
                prev = used[i];
            }
        }
    }
    prev->right = first;
    first->left = prev;
    heap->min = min;
}

void *get_top(FibonacciHeap *heap) {
    if (heap->min == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return heap->min->data;
    }
}

void extract(FibonacciHeap *heap) {
    struct Node *root = heap->min;
    if (root == NULL) {
        exit(EXIT_FAILURE);
    }
    struct Node *child = root->child;
    if (child != NULL) {
        union_roots(root, child);
        root->child = NULL;
    }
    if (root->right == root) {
        heap->min = NULL;
    } else {
        struct Node *left = root->left;
        struct Node *right = root->right;
        left->right = right;
        right->left = left;
        heap->min = right;
        consolidate(heap);
    }
    free(root->data);
    free(root);
}

void clear_nodes(struct Node *curr_node) {
    struct Node *start = curr_node;
    curr_node = curr_node->right;
    while (curr_node != start) {
        if (curr_node->child != NULL) {
            clear_nodes(curr_node->child);
        }
        struct Node *next = curr_node->right;
        free(curr_node->data);
        free(curr_node);
        curr_node = next;
    }
    if (start->child != NULL) {
        clear_nodes(start->child);
    }
    free(start->data);
    free(start);
}

void clear_heap(FibonacciHeap *heap) {
    if (heap->min != NULL) {
        clear_nodes(heap->min);
    }
    free(heap);
}


typedef struct {
    FibonacciHeap *heap;
    bool (*cmp)(void *, void *);
    int size;
} PriorityQueue;

PriorityQueue *priority_queue_init(bool (*cmp)(void *, void *)) {
    PriorityQueue *new = malloc(sizeof(PriorityQueue));
    new->heap = heap_init(cmp);
    new->size = 0;
    return new;
}

void push(PriorityQueue *queue, void *data, size_t size_data) {
    insert(queue->heap, data, size_data);
    queue->size++;
}

void *top(PriorityQueue *queue) {
    return get_top(queue->heap);
}

int size(PriorityQueue *queue) {
    return queue->size;
}

void pop(PriorityQueue *queue) {
    extract(queue->heap);
    queue->size--;
}

bool empty(PriorityQueue *queue) {
    return queue->size == 0;
}

void clear_priority_queue(PriorityQueue *queue) {
    clear_heap(queue->heap);
    free(queue);
}