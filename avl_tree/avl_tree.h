#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct AvlTree AvlTree;

AvlTree *tree_init(void);

void clear_tree(AvlTree *tree);

int get_height(AvlTree *tree);

void add(AvlTree *tree, int value);

#endif //AVL_TREE_H
