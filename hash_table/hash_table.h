#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct HashTable HashTable;

HashTable *table_init(int capacity);

void clear_table(HashTable *table);

int get_size(HashTable *table);

bool consist(HashTable *table, void *key, size_t size_key);

void *get(HashTable *table, void *key, size_t size_key);

void update(HashTable *table, void *key, size_t size_key, void *value, size_t size_value);

void delete(HashTable *table, void *key, size_t size_key);

#endif //HASH_TABLE_H