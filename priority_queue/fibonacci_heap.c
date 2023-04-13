#include <stdlib.h>
#include <stdbool.h>

#define MAX_AMOUNT_ROOTS 64

static struct Node {
    struct Node *child;
    struct Node *left;
    struct Node *right;
    int value;
    int rank;
} node;

typedef struct FibonacciHeap {
    struct Node *min;
} FibonacciHeap;

struct Node *node_init(int value) {
    struct Node *new_node = malloc(sizeof(node));
    *new_node = (struct Node) {NULL, NULL, NULL, value, 0};
    return new_node;
}

FibonacciHeap *heap_init(void) {
    FibonacciHeap *new_heap = malloc(sizeof(FibonacciHeap));
    new_heap->min = NULL;
    return new_heap;
}


void insert(FibonacciHeap *heap, int value) {
    struct Node *new_node = node_init(value);
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
    if (value < heap->min->value) {
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

struct Node *merge(struct Node *first, struct Node *second) {
    if (first->value < second->value) {
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
                curr_node = merge(curr_node, used[rank]);
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
            if (used[i]->value <= min->value) {
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

int get_min(FibonacciHeap *heap) {
    if (heap->min == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return heap->min->value;
    }
}

int extract_min(FibonacciHeap *heap) {
    struct Node *root = heap->min;
    if (root == NULL) {
        exit(EXIT_FAILURE);
    }
    struct Node *child = root->child;
    if (child != NULL) {
        union_roots(root, child);
        root->child = NULL;
    }
    int res = root->value;
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
    free(root);
    return res;
}

void clear_nodes(struct Node *curr_node) {
    struct Node *start = curr_node;
    curr_node = curr_node->right;
    while (curr_node != start) {
        if (curr_node->child != NULL) {
            clear_nodes(curr_node->child);
        }
        struct Node *next = curr_node->right;
        free(curr_node);
        curr_node = next;
    }
    if (start->child != NULL) {
        clear_nodes(start->child);
    }
    free(start);
}

void clear_heap(FibonacciHeap *heap) {
    if (heap->min != NULL) {
        clear_nodes(heap->min);
    }
    free(heap);
}
