#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct List List;

typedef struct ListNode ListNode;

List *list_init(void);

void clear_list(List *list);

void push_front(List *list, void *data, size_t size_data);

void push_back(List *list, void *data, size_t size_data);

void *front(List *list);

void *back(List *list);

void pop_back(List *list);

void pop_front(List *list);

bool empty(List *list);

ListNode *begin(List *list);

ListNode *end(List *list);

ListNode *next(ListNode *node);

ListNode  *prev(ListNode *node);

void *get_data(ListNode *node);

int get_len(List *list);

void *get(List *list, int ind);

void insert(List *list, int ind, void *data, size_t size_data);

void delete(List *list, int ind);

#endif //LIST_H
