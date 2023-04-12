#include <stdlib.h>

static struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

struct Node *node_init(int key) {
    struct Node *new_node = malloc(sizeof(struct Node));
    *new_node = (struct Node) {key, 1, NULL, NULL};
    return new_node;
}

static int height(struct Node *n) {
    return (n == NULL) ? 0 : n->height;
}

static int balance_factor(struct Node *n) {
    return height(n->right) - height(n->left);
}

static void fix_height(struct Node *n) {
    int h1 = height(n->left);
    int h2 = height(n->right);
    n->height = (h1 > h2 ? h1 : h2) + 1;
}

static struct Node *rotate_right(struct Node *n) {
    struct Node *left = n->left;
    n->left = left->right;
    left->right = n;
    fix_height(n);
    fix_height(left);
    return left;
}

static struct Node *rotate_left(struct Node *n) {
    struct Node *right = n->right;
    n->right = right->left;
    right->left = n;
    fix_height(n);
    fix_height(right);
    return right;
}

static struct Node *balance(struct Node *n) {
    fix_height(n);
    if (balance_factor(n) == 2) {
        if (balance_factor(n->right) < 0) {
            n->right = rotate_right(n->right);
        }
        return rotate_left(n);
    }
    if (balance_factor(n) == -2) {
        if (balance_factor(n->left) > 0) {
            n->left = rotate_left(n->left);
        }
        return rotate_right(n);
    }
    return n;
}

typedef struct {
    struct Node *root;
} AvlTree;

static struct Node *insert(struct Node *curr_node, int key) {
    if (!curr_node) {
        return node_init(key);
    }
    if (key < curr_node->key) {
        curr_node->left = insert(curr_node->left, key);
    } else {
        curr_node->right = insert(curr_node->right, key);
    }
    return balance(curr_node);
}

AvlTree *tree_init(void) {
    AvlTree *new_tree = malloc(sizeof(AvlTree));
    new_tree->root = NULL;
    return new_tree;
}

void add(AvlTree *tree, int key) {
    if (tree->root == NULL) {
        struct Node *new_node = node_init(key);
        tree->root = new_node;
    } else {
        tree->root = insert(tree->root, key);
    }
}

int get_height(AvlTree *tree) {
    return tree->root == NULL ? 0 : tree->root->height;
}

static void clear_nodes(struct Node *curr) {
    if (curr->left != NULL) {
        clear_nodes(curr->left);
    }
    if (curr->right != NULL) {
        clear_nodes(curr->right);
    }
    free(curr);
}

void clear_tree(AvlTree *tree) {
    if (tree->root != NULL) {
        clear_nodes(tree->root);
    }
    free(tree);
}
