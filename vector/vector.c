#include <stdlib.h>
#include <string.h>

typedef struct vector {
    int *array;
    int size;
    int capacity;
} vector;

vector *vector_init(int size) {
    vector *new = malloc(sizeof(vector));
    if (size == 0) {
        size = 10;
    }
    new->array = calloc(size, sizeof(int));
    new->capacity = size;
    new->size = 0;
    return new;
}

void push_back(vector *v, int value) {
    if (v->size < v->capacity) {
        v->array[v->size] = value;
        v->size++;
    } else {
        int new_size = v->capacity * 2;
        int *tmp = realloc(v->array, sizeof(int) * new_size);
        if (tmp != NULL) {
            v->array = tmp;
            v->capacity = new_size;
            push_back(v, value);
        } else {
            exit(EXIT_FAILURE);
        }
    }
}

void shrink_to_fit(vector *v) {
    if (v->size != v->capacity) {
        v->array = realloc(v->array, v->size);
        v->capacity = v->size;
    }
}

void resize(vector *v, int new_size) {
    if (new_size < v->size) {
        v->size = new_size;
    } else {
        int *tmp = realloc(v->array, new_size);
        if (tmp == NULL) {
            exit(EXIT_FAILURE);
        }
        for (int i = v->size; i < new_size; i++) {
            tmp[i] = 0;
        }
        v->array = tmp;
    }
}

void pop_back(vector *v) {
    if (v->size == 0) {
        exit(EXIT_FAILURE);
    } else {
        v->size--;
    }
}

void clear_vector(vector *v) {
    free(v->array);
    free(v);
}

int get_size(vector *v) {
    return v->size;
}

int get(vector *v, int ind) {
    return v->array[ind];
}
