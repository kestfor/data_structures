#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdbool.h>

typedef struct ForwardList ForwardList;

typedef struct ListNode ListNode;

ForwardList *list_init(void);

void clear_list(ForwardList *list);

void push_front(ForwardList *list, int data);

int front(ForwardList *list);

void pop_front(ForwardList *list);

bool empty(ForwardList *list);

ListNode *begin(ForwardList *list);

ListNode *next(ListNode *node);

int get_data(ListNode *node);

int get_len(ForwardList *list);

int get(ForwardList *list, int ind);

void insert(ForwardList *list, int ind, int data);

void delete(ForwardList *list, int ind);

#endif //FORWARD_LIST_H
