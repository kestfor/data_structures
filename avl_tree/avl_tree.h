#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>

typedef struct AvlTree AvlTree;

AvlTree *tree_init(void);

void clear_tree(AvlTree *tree);

int get_height(AvlTree *tree);

void add(AvlTree *tree, int key);

void traverse(AvlTree *tree, FILE *stream);

void delete(AvlTree *tree, int key);

bool consist(AvlTree *tree, int key);

#endif //AVL_TREE_H
