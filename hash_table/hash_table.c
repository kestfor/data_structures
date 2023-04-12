#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define M 1000000009
#define P 257
#define CAPACITY 50000

static size_t min(size_t first, size_t second) {
    return first < second ? first : second;
}

typedef struct {
    char *key;
    int value;
} HashTableItem;

static HashTableItem *table_item_init(char *key, int value) {
    HashTableItem *new = malloc(sizeof(HashTableItem));
    new->value = value;
    size_t len = strlen(key);
    new->key = calloc(len + 1, sizeof(char));
    strncpy(new->key, key, len);
    return new;
}

void clear_table_item(HashTableItem *item) {
    free(item->key);
    free(item);
}

static struct LinkedList {
    HashTableItem *item;
    struct LinkedList *next;
} LinkedList;

static struct LinkedList *list_init(HashTableItem *item) {
    struct LinkedList *new = malloc(sizeof(struct LinkedList));
    new->item = item;
    new->next = NULL;
    return new;
}

static struct LinkedList *push_front(struct LinkedList *head, HashTableItem *item) {
    struct LinkedList *new_head = calloc(1, sizeof(struct LinkedList));
    new_head->item =  item;
    new_head->next = head;
    return new_head;
}

static void clear_list(struct LinkedList *head) {
    struct LinkedList *curr = head;
    while (curr != NULL) {
        struct LinkedList *next = curr->next;
        free(curr);
        curr = next;
    }
}

static int hash(char *key) {
    long long res = 0;
    long long pow = 1;
    size_t len = strlen(key);
    for (size_t i = 0; i < len; i++) {
        res = (res % M + key[i] * (pow % M)) % M;
        pow = (pow * P) % LONG_LONG_MAX;
    }
    return (int) res;
}

typedef struct {
    HashTableItem **bucket;
    struct LinkedList **overflow_bucket;
    int size;
} HashTable;

HashTable *table_init(void) {
    HashTable *new = malloc(sizeof(HashTable));
    new->bucket = calloc(CAPACITY, sizeof(HashTableItem*));
    new->overflow_bucket = calloc(CAPACITY, sizeof(struct LinkedList*));
    new->size = 0;
    return new;
}

void clear_table(HashTable *table) {
    for (int i = 0; i < CAPACITY; i++) {
        if (table->bucket[i] != NULL) {
            clear_table_item(table->bucket[i]);
        }
        if (table->overflow_bucket[i] != NULL) {
            clear_list(table->overflow_bucket[i]);
        }
    }
    free(table->overflow_bucket);
    free(table->bucket);
    free(table);
}

static void handle_collision(HashTable *table, int ind, char *key, int value) {
    struct LinkedList *list = NULL;
    if (table->overflow_bucket[ind] == NULL) {
        list = list_init(table->bucket[ind]);
    } else {
        list = table->overflow_bucket[ind];
    }
    list = push_front(list, table_item_init(key, value));
    table->overflow_bucket[ind] = list;
    table->size++;
}

static void insert(HashTable *table, char *key, int value) {
    int ind = hash(key) % CAPACITY;
    if (table->bucket[ind] == NULL) {
        table->bucket[ind] = table_item_init(key, value);
        table->size++;
    } else {
        handle_collision(table, ind, key, value);
    }
}

HashTableItem *get_item(HashTable *table, char *key) {
    int ind = hash(key) % CAPACITY;
    if (table->overflow_bucket[ind] == NULL) {
        if (table->bucket[ind] != NULL) {
            return table->bucket[ind];
        } else {
            return NULL;
        }
    } else {
        struct LinkedList *curr = table->overflow_bucket[ind];
        while (curr != NULL) {
            if (strncmp(curr->item->key, key, min(strlen(curr->item->key), strlen(key))) == 0) {
                return curr->item;
            }
            curr = curr->next;
        }
        return NULL;
    }
}

int get(HashTable *table, char *key) {
    HashTableItem *item = get_item(table, key);
    if (item == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return item->value;
    }
}

bool consist(HashTable *table, char *key) {
    return get_item(table, key) != NULL;
}

void delete(HashTable *table, char *key) {
    int ind = hash(key) % CAPACITY;
    if (table->overflow_bucket[ind] != NULL || table->bucket[ind] != NULL) {
        if (table->overflow_bucket[ind] != NULL) {
            struct LinkedList *curr = table->overflow_bucket[ind];
            if (strncmp(curr->item->key, key, min(strlen(curr->item->key), strlen(key))) == 0) {
                table->overflow_bucket[ind] = curr->next;
                clear_table_item(curr->item);
                free(curr);
            } else {
                struct LinkedList *prev = curr;
                while (curr != NULL) {
                    if (strncmp(curr->item->key, key, min(strlen(curr->item->key), strlen(key))) == 0) {
                        prev->next = curr->next;
                        clear_table_item(curr->item);
                        free(curr);
                        return;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
        } else {
            clear_table_item(table->bucket[ind]);
            table->bucket[ind] = NULL;
        }

    }
}

int get_size(HashTable *table) {
    return table->size;
}

void update(HashTable *table, char *key, int value) {
    int ind = hash(key) % CAPACITY;
    if (table->overflow_bucket[ind] != NULL || table->bucket[ind] != NULL) {
        HashTableItem *item = get_item(table, key);
        item->value = value;
    } else {
        insert(table, key, value);
    }
}