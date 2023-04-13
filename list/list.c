#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    int data;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    int len;
} List;

static ListNode *node_init(int data) {
    ListNode *new = malloc(sizeof(ListNode));
    new->data = data;
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
            free(curr);
            curr = next;
        }
    }
    free(list);
}

void push_front(List *list, int data) {
    if (list->head == NULL) {
        list->head = list->tail = node_init(data);
    } else {
        ListNode *new_head = node_init(data);
        new_head->next = list->head;
        list->head->prev = new_head;
        list->head = new_head;
    }
    list->len++;
}

void push_back(List *list, int data) {
    if (list->tail == NULL) {
        list->tail = list->head = node_init(data);
    } else {
        ListNode *new_tail = node_init(data);
        list->tail->next = new_tail;
        new_tail->prev = list->tail;
        list->tail = new_tail;
    }
    list->len++;
}

int front(List *list) {
    if (list->head == NULL) {
        exit(EXIT_FAILURE);
    } else {
        return list->head->data;
    }
}

int back(List *list) {
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
            free(list->head);
            list->head = list->tail = NULL;
        } else {
            list->tail = list->tail->prev;
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
            free(list->tail);
            list->tail = list->head = NULL;
        } else {
            list->head = list->head->next;
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

int get_data(ListNode *node) {
    return node->data;
}

int get_len(List *list) {
    return list->len;
}

static ListNode *get_node(List *list, int ind) {
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

int get(List *list, int ind) {
    return get_node(list, ind)->data;
}

void insert(List *list, int ind, int data) {
    if (ind == 0) {
        push_front(list, data);
        return;
    }
    if (ind == get_len(list)) {
        push_back(list, data);
        return;
    }
    ListNode *curr = get_node(list, ind);
    ListNode *tmp = curr->prev;
    tmp->next = node_init(data);
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
    free(node_to_del);
    list->len--;
}
