#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *data;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    int len;
} List;

static ListNode *node_init(void *data, size_t size_data) {
    ListNode *new = malloc(sizeof(ListNode));
    new->data = malloc(size_data);
    memcpy(new->data, data, size_data);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

List *list_init(void) {
    List *new = malloc(sizeof(List));
    new->head = NULL;
    new->tail = NULL;
    new->len = 0;
    return new;
}

void clear_list(List *list) {
    if (list->head != NULL) {
        ListNode *curr = list->head;
        while (curr != NULL) {
            ListNode *next = curr->next;
            free(curr->data);
            free(curr);
            curr = next;
        }
    }
    free(list);
}

void push_front(List *list, void *data, size_t size_data) {
    if (list->head == NULL) {
        list->head = list->tail = node_init(data, size_data);
    } else {
        ListNode *new_head = node_init(data, size_data);
        new_head->next = list->head;
        list->head->prev = new_head;
        list->head = new_head;
    }
    list->len++;
}

void push_back(List *list, void *data, size_t size_data) {
    if (list->tail == NULL) {
        list->tail = list->head = node_init(data, size_data);
    } else {
        ListNode *new_tail = node_init(data, size_data);
        list->tail->next = new_tail;
        new_tail->prev = list->tail;
        list->tail = new_tail;
    }
    list->len++;
}

void *front(List *list) {
    if (list->head == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return list->head->data;
    }
}

void *back(List *list) {
    if (list->tail == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return list->tail->data;
    }
}

void pop_back(List *list) {
    if (list->tail == NULL) {
        exit(EXIT_FAILURE);
    } else {
        if (list->head == list->tail) {
            free(list->head->data);
            free(list->head);
            list->head = list->tail = NULL;
        } else {
            list->tail = list->tail->prev;
            free(list->tail->next->data);
            free(list->tail->next);
            list->tail->next = NULL;
        }
    }
    list->len--;
}

void pop_front(List *list) {
    if (list->head == NULL) {
        exit(EXIT_FAILURE);
    } else {
        if (list->head == list->tail) {
            free(list->tail->data);
            free(list->tail);
            list->tail = list->head = NULL;
        } else {
            list->head = list->head->next;
            free(list->head->prev->data);
            free(list->head->prev);
            list->head->prev = NULL;
        }
    }
    list->len--;
}

bool empty(List *list) {
    return list->head == NULL;
}

ListNode *begin(List *list) {
    return list->head;
}

ListNode *end(List *list) {
    return list->tail;
}

ListNode *next(ListNode *node) {
    return node->next;
}

ListNode  *prev(ListNode *node) {
    return node->prev;
}

void *get_data(ListNode *node) {
    return node->data;
}

int get_len(List *list) {
    return list->len;
}

static ListNode *get_node(List *list, int ind) {
    if (list->len - ind > ind) {
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
    } else {
        int curr_ind = list->len - 1;
        if (list->tail == NULL) {
            exit(EXIT_FAILURE);
        }
        ListNode *curr = end(list);
        while (curr != NULL) {
            if (curr_ind == ind) {
                return curr;
            }
            curr_ind--;
            curr = curr->prev;
        }
        exit(EXIT_FAILURE);
    }
}

void *get(List *list, int ind) {
    return get_node(list, ind)->data;
}

void insert(List *list, int ind, void *data, size_t size_data) {
    if (ind == 0) {
        push_front(list, data, size_data);
        return;
    }
    if (ind == get_len(list)) {
        push_back(list, data, size_data);
        return;
    }
    ListNode *curr = get_node(list, ind);
    ListNode *tmp = curr->prev;
    tmp->next = node_init(data, size_data);
    tmp->next->next = curr;
    tmp->next->prev = tmp;
    curr->prev = tmp->next;
    list->len++;
}

void delete(List *list, int ind) {
    if (ind == 0) {
        pop_front(list);
        return;
    }
    if (ind == get_len(list)) {
        pop_back(list);
        return;
    }
    ListNode *node_to_del = get_node(list, ind);
    node_to_del->prev->next = node_to_del->next;
    node_to_del->next->prev = node_to_del->prev;
    free(node_to_del->data);
    free(node_to_del);
    list->len--;
}
