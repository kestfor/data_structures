#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static struct Node {
    int key;
    long long value;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

struct Node *node_init(int key, long long value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    *new_node = (struct Node) {key, value, 1, NULL, NULL};
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

static struct Node *insert(struct Node *curr_node, int key, long long value) {
    if (!curr_node) {
        return node_init(key, value);
    }
    if (curr_node->key == key) {
        curr_node->value = value;
    }
    if (key < curr_node->key) {
        curr_node->left = insert(curr_node->left, key, value);
    } else {
        curr_node->right = insert(curr_node->right, key, value);
    }
    return balance(curr_node);
}

AvlTree *tree_init(void) {
    AvlTree *new_tree = malloc(sizeof(AvlTree));
    new_tree->root = NULL;
    return new_tree;
}

void add(AvlTree *tree, int key, long long value) {
    if (tree->root == NULL) {
        struct Node *new_node = node_init(key, value);
        tree->root = new_node;
    } else {
        tree->root = insert(tree->root, key, value);
    }
}

static struct Node *find(struct Node *curr, int key) {
    if (curr == NULL) {
        return NULL;
    }
    if (curr->key == key) {
        return curr;
    } else {
        if (key < curr->key) {
            return find(curr->left, key);
        } else {
            return find(curr->right, key);
        }
    }
}

long long get(AvlTree *tree, int key) {
    struct Node *res = find(tree->root, key);
    if (res == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return res->value;
    }
}

bool consist(AvlTree *tree, int key) {
    if (tree->root == NULL) {
        return false;
    } else {
        return find(tree->root, key) != NULL;
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

static struct Node* find_min(struct Node* node) {
    return node->left != NULL ? find_min(node->left) : node;
}

static struct Node* remove_min(struct Node* node) {
    if (node->left==0 )
        return node->right;
    node->left = remove_min(node->left);
    return balance(node);
}

static struct Node* remove_node(struct Node* node, int key) {
    if (node == NULL) {
        return NULL;
    }
    if (key < node->key) {
        node->left = remove_node(node->left, key);
    } else if (key > node->key) {
        node->right = remove_node(node->right, key);
    } else {
        struct Node *left = node->left;
        struct Node *right = node->right;
        free(node);
        if (right == NULL) {
            return left;
        }
        struct Node *min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}

void delete(AvlTree *tree, int key) {
    if (tree->root == NULL) {
        return;
    } else {
        tree->root = remove_node(tree->root, key);
    }
}

static void print_nodes(struct Node *curr, FILE *stream) {
    if (curr->left != NULL) {
        print_nodes(curr->left, stream);
    }
    fprintf(stream, "%lld ", curr->value);
    if (curr->right != NULL) {
        print_nodes(curr->right, stream);
    }
}

void traverse(AvlTree *tree, FILE *stream) {
    print_nodes(tree->root, stream);
}

void clear_tree(AvlTree *tree) {
    if (tree->root != NULL) {
        clear_nodes(tree->root);
    }
    free(tree);
}
