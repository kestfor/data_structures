#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector vector;

vector *vector_init(int size);

void push_back(vector *v, int value);

void shrink_to_fit(vector *v);

void resize(vector *v, int new_size);

void pop_back(vector *v);

int get(vector *v, int ind);

int get_size(vector *v);

void clear_vector(vector *v);

#endif //VECTOR_H
