#include "linkedlist.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static Node *create_node(const void *data_ptr, size_t item_size) {
    assert(data_ptr);

    Node *node = malloc(sizeof(Node));
    void *data = malloc(item_size);
    memcpy(data, data_ptr, item_size);

    assert(node && data);

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
};

void linkedlist_init(LinkedList *list, size_t item_size) {
    list->head = NULL;
    list->tail = NULL;
    list->item_size = item_size;
    list->size = 0;
};

void linkedlist_push_front(LinkedList *list, const void *data_ptr) {
    Node *new = create_node(data_ptr, list->item_size);
    Node *head = list->head;

    list->head = new;
    if (list->size == 0) {
        list->tail = new;
    } else {
        assert(head);
        head->prev = new;
        new->next = head;
    }

    list->size++;
};

void linkedlist_push_back(LinkedList *list, const void *data_ptr) {
    Node *new = create_node(data_ptr, list->item_size);
    Node *tail = list->tail;

    list->tail = new;
    if (list->size == 0) {
        list->head = new;
    } else {
        assert(tail);
        tail->next = new;
        new->prev = tail;
    }

    list->size++;
};

bool linkedlist_pop_front(LinkedList *list, void *out_ptr) {
    if (list->size == 0) {
        return false;
    };

    Node *head = list->head;

    if (out_ptr) {
        memcpy(out_ptr, head->data, list->item_size);
    }

    Node *next = head->next;
    if (next) {
        list->head = next;
        next->prev = NULL;
    }

    free(head->data);
    free(head);

    list->size--;

    return true;
};

bool linkedlist_pop_back(LinkedList *list, void *out_ptr) {};

void linkedlist_insert_after(Node *node, const void *data_ptr,
                             size_t item_size) {};
void linkedlist_remove(LinkedList *list, Node *node_ptr) {};

void linkedlist_clear(LinkedList *list) {};