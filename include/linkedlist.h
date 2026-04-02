#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
    size_t item_size;
} LinkedList;

static Node *create_node(const void *data_ptr, size_t item_size);
void linkedlist_init(LinkedList *list, size_t item_size);
void linkedlist_push_front(LinkedList *list, const void *data_ptr);
void linkedlist_push_back(LinkedList *list, const void *data_ptr);
bool linkedlist_pop_front(LinkedList *list, void *out_ptr);
bool linkedlist_pop_back(LinkedList *list, void *out_ptr);

void linkedlist_insert_after(Node *node, const void *data_ptr,
                             size_t item_size);
void linkedlist_remove(LinkedList *list, Node *node_ptr);

void linkedlist_clear(LinkedList *list);

#endif