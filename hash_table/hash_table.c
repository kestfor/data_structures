#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool equal(void *first, size_t size_first, void *second, size_t size_second) {
    if (size_first != size_second) {
        return false;
    }
    for (size_t i = 0; i < size_first; i++) {
        unsigned char first_byte = *((unsigned char *) (first) + i);
        unsigned char second_byte = *((unsigned char *) (second) + i);
        if (first_byte != second_byte) {
            return false;
        }
    }
    return true;
}

typedef struct {
    void *key;
    size_t size_key;
    void *value;
} HashTableItem;

static HashTableItem *table_item_init(void *key, size_t size_key, void *value, size_t size_value) {
    HashTableItem *new = malloc(sizeof(HashTableItem));
    new->key = malloc(size_key);
    new->size_key = size_key;
    new->value = malloc(size_value);
    memcpy(new->key, key, size_key);
    memcpy(new->value, value, size_value);
    return new;
}

void clear_table_item(HashTableItem *item) {
    free(item->key);
    free(item->value);
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

static unsigned int hash(const unsigned char *key, size_t len) {
    unsigned int hash = 0;
    for(size_t i = 0; i < len; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

typedef struct {
    HashTableItem **bucket;
    struct LinkedList **overflow_bucket;
    int size;
    int capacity;
} HashTable;

HashTable *table_init(int capacity) {
    HashTable *new = malloc(sizeof(HashTable));
    new->bucket = calloc(capacity, sizeof(HashTableItem*));
    new->overflow_bucket = calloc(capacity, sizeof(struct LinkedList*));
    new->capacity = capacity;
    new->size = 0;
    return new;
}

void clear_table(HashTable *table) {
    for (int i = 0; i < table->capacity; i++) {
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

static void handle_collision(HashTable *table, unsigned int ind, void *key, size_t size_key, void *value, size_t size_value) {
    struct LinkedList *list = NULL;
    if (table->overflow_bucket[ind] == NULL) {
        list = list_init(table->bucket[ind]);
    } else {
        list = table->overflow_bucket[ind];
    }
    list = push_front(list, table_item_init(key, size_key, value, size_value));
    table->overflow_bucket[ind] = list;
    table->size++;
}

static void insert(HashTable *table, void *key, size_t size_key, void *value, size_t size_value) {
    unsigned int ind = hash(key, size_key) % table->capacity;
    if (table->bucket[ind] == NULL) {
        table->bucket[ind] = table_item_init(key, size_key, value, size_value);
        table->size++;
    } else {
        handle_collision(table, ind, key, size_key, value, size_value);
    }
}

static HashTableItem *get_item(HashTable *table, void *key, size_t size_key) {
    unsigned int ind = hash(key, size_key) % table->capacity;
    if (table->overflow_bucket[ind] == NULL) {
        if (table->bucket[ind] != NULL) {
            return table->bucket[ind];
        } else {
            return NULL;
        }
    } else {
        struct LinkedList *curr = table->overflow_bucket[ind];
        while (curr != NULL) {
            if (equal(curr->item->key, curr->item->size_key, key, size_key)) {
                return curr->item;
            }
            curr = curr->next;
        }
        return NULL;
    }
}

void *get(HashTable *table, void *key, size_t size_key) {
    HashTableItem *item = get_item(table, key, size_key);
    if (item == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return item->value;
    }
}

bool consist(HashTable *table, void *key, size_t size_key) {
    return get_item(table, key, size_key) != NULL;
}

void delete(HashTable *table, void *key, size_t size_key) {
    unsigned int ind = hash(key, size_key) % table->capacity;
    if (table->overflow_bucket[ind] != NULL || table->bucket[ind] != NULL) {
        if (table->overflow_bucket[ind] != NULL) {
            struct LinkedList *curr = table->overflow_bucket[ind];
            if (equal(curr->item->key, curr->item->size_key, key, size_key)) {
                table->overflow_bucket[ind] = curr->next;
                clear_table_item(curr->item);
                free(curr);
                table->size--;
            } else {
                struct LinkedList *prev = curr;
                while (curr != NULL) {
                    if (equal(curr->item->key, curr->item->size_key, key, size_key)) {
                        prev->next = curr->next;
                        clear_table_item(curr->item);
                        free(curr);
                        table->size--;
                        return;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
        } else {
            clear_table_item(table->bucket[ind]);
            table->bucket[ind] = NULL;
            table->size--;
        }

    }
}

int get_size(HashTable *table) {
    return table->size;
}

void update(HashTable *table, void *key, size_t size_key, void *value, size_t size_value) {
    unsigned int ind = hash(key, size_key) % table->capacity;
    if (table->overflow_bucket[ind] != NULL || table->bucket[ind] != NULL) {
        HashTableItem *item = get_item(table, key, size_key);
        memcpy(item->value, value, size_value);
    } else {
        insert(table, key, size_key, value, size_value);
    }
}