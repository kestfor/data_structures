#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

typedef struct HashTable HashTable;

HashTable *table_init(void);

void clear_table(HashTable *table);

int get_size(HashTable *table);

bool consist(HashTable *table, char *key);

int get(HashTable *table, char *key);

void update(HashTable *table, char *key, int value);

void delete(HashTable *table, char *key);

#endif //HASH_TABLE_H