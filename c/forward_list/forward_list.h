#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct ForwardList ForwardList;

typedef struct ListNode ListNode;

ForwardList *list_init(void);

void clear_list(ForwardList *list);

void push_front(ForwardList *list, void *data, size_t size_data);

void *front(ForwardList *list);

void pop_front(ForwardList *list);

bool empty(ForwardList *list);

ListNode *begin(ForwardList *list);

ListNode *next(ListNode *node);

void *get_data(ListNode *node);

int get_len(ForwardList *list);

void *get(ForwardList *list, int ind);

void insert(ForwardList *list, int ind, void *data, size_t size_data);

void delete(ForwardList *list, int ind);

#endif //FORWARD_LIST_H
