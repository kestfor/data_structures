#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static struct Node {
    void *key;
    void *data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

struct Node *node_init(void *key, size_t size_key, void *data, size_t size_data) {
    struct Node *new_node = malloc(sizeof(struct Node));
    *new_node = (struct Node) {NULL, NULL, 1, NULL, NULL};
    new_node->key = malloc(size_key);
    new_node->data = malloc(size_data);
    memcpy(new_node->key, key, size_key);
    memcpy(new_node->data, data, size_data);
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
    bool (*cmp) (void *, void *);
} AvlTree;

static struct Node *insert(struct Node *curr_node, void *key, size_t size_key, void *data, size_t size_data, bool (*cmp)(void *, void*)) {
    if (!curr_node) {
        return node_init(key, size_key, data, size_data);
    }
    bool left = cmp(key, curr_node->key);
    bool right = cmp(curr_node->key, key);
    if (!left && !right) {
        memcpy(curr_node->data, data, size_data);
    }
    if (left) {
        curr_node->left = insert(curr_node->left, key, size_key, data, size_data, cmp);
    } else {
        curr_node->right = insert(curr_node->right, key, size_key, data, size_data, cmp);
    }
    return balance(curr_node);
}

AvlTree *tree_init(bool (*cmp)(void *, void *)) {
    AvlTree *new_tree = malloc(sizeof(AvlTree));
    new_tree->root = NULL;
    new_tree->cmp = cmp;
    return new_tree;
}

void add(AvlTree *tree, void *key, size_t size_key, void *data, size_t size_data) {
    if (tree->root == NULL) {
        struct Node *new_node = node_init(key, size_key, data, size_data);
        tree->root = new_node;
    } else {
        tree->root = insert(tree->root, key, size_key, data, size_data, tree->cmp);
    }
}

static struct Node *find(struct Node *curr, void *key, size_t size_key, bool (*cmp)(void *, void *)) {
    if (curr == NULL) {
        return NULL;
    }
    bool left = cmp(key, curr->key);
    bool right = cmp(curr->key, key);
    if (!left && !right) {
        return curr;
    } else {
        if (left) {
            return find(curr->left, key, size_key, cmp);
        } else {
            return find(curr->right, key, size_key, cmp);
        }
    }
}

void *get(AvlTree *tree, void *key, size_t size_key) {
    struct Node *res = find(tree->root, key, size_key, tree->cmp);
    if (res == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return res->data;
    }
}

bool consist(AvlTree *tree, void *key, size_t size_key) {
    if (tree->root == NULL) {
        return false;
    } else {
        return find(tree->root, key, size_key, tree->cmp) != NULL;
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
    free(curr->key);
    free(curr->data);
    free(curr);
}

static struct Node* find_min(struct Node* node) {
    return node->left != NULL ? find_min(node->left) : node;
}

static struct Node* remove_min(struct Node* node) {
    if (node->left == NULL) {
        return node->right;
    }
    node->left = remove_min(node->left);
    return balance(node);
}

static struct Node* remove_node(struct Node* node, void *key, size_t size_key, bool (*cmp)(void *, void *)) {
    if (node == NULL) {
        return NULL;
    }
    if (cmp(key, node->key)) {
        node->left = remove_node(node->left, key, size_key, cmp);
    } else if (cmp(node->key, key)) {
        node->right = remove_node(node->right, key, size_key, cmp);
    } else {
        struct Node *left = node->left;
        struct Node *right = node->right;
        free(node->key);
        free(node->data);
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

void delete(AvlTree *tree, void *key, size_t size_key) {
    if (tree->root == NULL) {
        return;
    } else {
        tree->root = remove_node(tree->root, key, size_key, tree->cmp);
    }
}

void clear_tree(AvlTree *tree) {
    if (tree->root != NULL) {
        clear_nodes(tree->root);
    }
    free(tree);
}
