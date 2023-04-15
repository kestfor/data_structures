#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vector vector;

vector *vector_init(int size);

void push_back(vector *v, void *value, size_t size_data);

void shrink_to_fit(vector *v);

void resize(vector *v, int new_size);

void pop_back(vector *v);

void *get(vector *v, int ind);

void set(vector *v, int ind, void *data, size_t size_data);

int get_size(vector *v);

void clear_vector(vector *v);

#endif //VECTOR_H
