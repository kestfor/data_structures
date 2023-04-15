#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct AvlTree AvlTree;

AvlTree *tree_init(bool (*cmp)(void *, void *));

void clear_tree(AvlTree *tree);

int get_height(AvlTree *tree);

void add(AvlTree *tree, void *key, size_t size_key, void *data, size_t size_data);

void *get(AvlTree *tree, void *key, size_t size_key);

void delete(AvlTree *tree, void *key, size_t size_key);

bool consist(AvlTree *tree, void *key, size_t size_key);

#endif //AVL_TREE_H
