#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode {
    struct ListNode *next;
    int data;
} ListNode;

typedef struct {
    ListNode *head;
    int len;
} ForwardList;

static ListNode *node_init(int data) {
    ListNode *new = malloc(sizeof(ListNode));
    new->data = data;
    new->next = NULL;
    return new;
}

ForwardList *list_init(void) {
    ForwardList *new = malloc(sizeof(ForwardList));
    new->head = NULL;
    new->len = 0;
    return new;
}

void clear_list(ForwardList *list) {
    if (list->head != NULL) {
        ListNode *curr = list->head;
        while (curr != NULL) {
            ListNode *next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(list);
}

void push_front(ForwardList *list, int data) {
    if (list->head == NULL) {
        list->head = node_init(data);
    } else {
        ListNode *new_head = node_init(data);
        new_head->next = list->head;
        list->head = new_head;
    }
    list->len++;
}

int front(ForwardList *list) {
    if (list->head == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return list->head->data;
    }
}

void pop_front(ForwardList *list) {
    if (list->head == NULL) {
        exit(EXIT_FAILURE);
    } else {
        ListNode *new_head = list->head->next;
        free(list->head);
        list->head = new_head;
    }
    list->len--;
}

bool empty(ForwardList *list) {
    return list->head == NULL;
}

ListNode *begin(ForwardList *list) {
    return list->head;
}

ListNode *next(ListNode *node) {
    return node->next;
}

int get_data(ListNode *node) {
    return node->data;
}

int get_len(ForwardList *list) {
    return list->len;
}

static ListNode *get_node(ForwardList *list, int ind) {
    int curr_ind = 0;
    if (list->head == NULL) {
        exit(EXIT_FAILURE);
    }
    ListNode *curr = begin(list);
    while (curr != NULL) {
        if (curr_ind == ind) {
            return curr;
        }
        curr_ind++;
        curr = curr->next;
    }
    exit(EXIT_FAILURE);
}

int get(ForwardList *list, int ind) {
    return get_node(list, ind)->data;
}

void insert(ForwardList *list, int ind, int data) {
    if (ind == 0) {
        push_front(list, data);
        return;
    }
    ListNode *curr = get_node(list, ind - 1);
    ListNode *tmp = curr->next;
    curr->next = node_init(data);
    curr->next->next = tmp;
    list->len++;
}

void delete(ForwardList *list, int ind) {
    if (ind == 0) {
        pop_front(list);
        return;
    }
    ListNode *tmp = get_node(list, ind - 1);
    ListNode *next = tmp->next->next;
    free(tmp->next);
    tmp->next = next;
    list->len--;
}
