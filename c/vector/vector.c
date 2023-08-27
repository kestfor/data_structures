#include <stdlib.h>
#include <string.h>

typedef struct vector {
    void **array;
    int size;
    int capacity;
} vector;

vector *vector_init(int size) {
    vector *new = malloc(sizeof(vector));
    if (size == 0) {
        size = 10;
    }
    new->array = calloc(size, sizeof(void*));
    new->capacity = size;
    new->size = 0;
    return new;
}

void push_back(vector *v, void *data, size_t size_data) {
    if (v->size < v->capacity) {
        v->array[v->size] = malloc(size_data);
        memcpy(v->array[v->size], data, size_data);
        v->size++;
    } else {
        int new_size = v->capacity * 2;
        void **tmp = realloc(v->array, sizeof(void*) * new_size);
        if (tmp != NULL) {
            v->array = tmp;
            v->capacity = new_size;
            push_back(v, data, size_data);
        } else {
            exit(EXIT_FAILURE);
        }
    }
}

void resize(vector *v, int new_size) {
    if (new_size < v->size) {
        v->size = new_size;
    } else {
        void **tmp = realloc(v->array, new_size * sizeof(void*));
        if (tmp == NULL) {
            exit(EXIT_FAILURE);
        }
        for (int i = v->size; i < new_size; i++) {
            tmp[i] = NULL;
        }
        v->array = tmp;
    }
}

void shrink_to_fit(vector *v) {
    if (v->size != v->capacity) {
        resize(v, v->size);
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
    for (int i = 0; i < v->capacity; i++) {
        if (v->array[i] != NULL) {
            free(v->array[i]);
        }
    }
    free(v->array);
    free(v);
}

int get_size(vector *v) {
    return v->size;
}

void *get(vector *v, int ind) {
    return v->array[ind];
}

void set(vector *v, int ind, void *data, size_t size_data) {
    if (ind >= v->capacity) {
        exit(EXIT_FAILURE);
    } else {
        if (v->array[ind] == NULL) {
            v->array[ind] = malloc(sizeof(size_data));
        }
        memcpy(v->array[ind], data, size_data);
    }
}
