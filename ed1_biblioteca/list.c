#include "list.h"

#include <stdlib.h>
#include <assert.h>

typedef struct list_node_ list_node_t;
struct list_node_ {
    void *data;
    list_node_t *prev, *next;
};

static list_node_t *
list_node_new(void *data)
{
    list_node_t *self = malloc(sizeof(list_node_t));

    if (self == NULL)
        return NULL;

    self->data = data;
    self->prev = self->next = NULL;

    return self;
}

static void
list_node_insert_after(list_node_t *self, list_node_t *node)
{
    node->next = self->next;
    node->prev = self;

    self->next->prev = node;
    self->next = node;
}

struct list_ {
    list_node_t head;

    compare_func_t comparator;
    destroy_func_t destructor;

    int n_elems;
};

list_t *
list_new_full(compare_func_t comparator, destroy_func_t destructor)
{
    list_t *self = malloc(sizeof(list_t));
    
    self->head.next = self->head.prev = &self->head;

    self->comparator = comparator ? comparator : general_cmp;
    self->destructor = destructor ? destructor : stub_destructor;

    self->n_elems = 0;

    return self;
}

list_t *
list_new(void)
{
    return list_new_full(NULL, NULL);
}

boolean
list_insert(list_t *self, int index, void *data) {
    list_node_t *n, *new_node;

    if (index < 0)
        return FALSE;
    else if (index > self->n_elems)
        return list_append(self, data);

    for (n = &self->head; index > 0; n = n->next)
        index--;

    new_node = list_node_new(data);
    if (new_node == NULL)
        return FALSE;

    list_node_insert_after(n, new_node);
    self->n_elems++;

    return TRUE;
}

boolean
list_append(list_t *self, void *data)
{
    list_node_t *new_node;

    new_node = list_node_new(data);
    if (new_node == NULL)
        return FALSE;

    list_node_insert_after(self->head.prev, new_node);
    self->n_elems++;

    return TRUE;
}

boolean
list_prepend(list_t *self, void *data)
{
    list_node_t *new_node;

    new_node = list_node_new(data);
    if (new_node == NULL)
        return FALSE;

    list_node_insert_after(&self->head, new_node);
    self->n_elems++;

    return TRUE;
}

static list_node_t *
list_find_node(list_t *self, void *data) {
    list_node_t *n;

    for (n = self->head.next; n != &self->head; n = n->next) {
        if (self->comparator(n->data, data) == 0) {
            return n;
        }
    }

    return NULL;
}

static list_node_t *
list_find_node_by_index(list_t *self, int index) {
    list_node_t *n;

    if (index < 0)
        return NULL;
    else if (index >= self->n_elems)
        return NULL;


    for (n = self->head.next; index > 0; n = n->next)
        index--;

    return n;
}

void *
list_remove(list_t *self, void *data)
{
    list_node_t *node = list_find_node(self, data);
    void *result;

    if (node == NULL)
        return NULL;

    node->prev->next = node->next;
    node->next->prev = node->prev;
    self->n_elems--;

    result = node->data;

    free(node);

    return result;
}

void *
list_find(list_t *self, void *data)
{
    list_node_t *node = list_find_node(self, data);

    return node == NULL ? NULL : node->data;
}

void *
list_get(list_t *self, int index)
{
    list_node_t *n;

    n = list_find_node_by_index(self, index);

    return n == NULL ? NULL : n->data;
}

void *
list_first(list_t *self)
{
    if (self->n_elems < 1)
        return NULL;

    return self->head.next->data;
}

void *
list_last(list_t *self)
{
    if (self->n_elems < 1)
        return NULL;

    return self->head.prev->data;
}


void
list_clear(list_t *self)
{
    list_node_t *n, *next;

    for (n = self->head.next; n != &self->head; n = next) {
        next = n->next;

        self->destructor(n->data);
        free(n);
    }

    self->head.next = self->head.prev = &self->head;
    self->n_elems = 0;
}

void
list_delete(list_t *self)
{
    list_clear(self);
    free(self);
}

int
list_size(list_t *self)
{
    return self->n_elems;
}

void
list_iterate(list_t *self, iterate_func_t itr, void *user_data)
{
    list_node_t *n;

    for (n = self->head.next; n != &self->head; n = n->next) {
        itr(n->data, user_data);
    }
}


typedef struct {
    iterator_t parent;
    list_t *list;
    list_node_t *node;
    int index;
} list_iterator_t;

static boolean list_iterator_has_more(iterator_t *self);
static void *list_iterator_get(iterator_t *self);
static void list_iterator_next(iterator_t *self);

iterator_t *
list_iterator(list_t *self) {
    list_iterator_t *itr = malloc(sizeof(list_iterator_t));

    itr->parent.has_more = list_iterator_has_more;
    itr->parent.get = list_iterator_get;
    itr->parent.next = list_iterator_next;
    itr->parent.delete = NULL;

    itr->list = self;
    itr->node = self->head.next;
    itr->index = 0;

    return (iterator_t *) itr;   
}

static boolean
list_iterator_has_more(iterator_t *self) {
    list_iterator_t *itr = (list_iterator_t *) self;

    return itr->node != &itr->list->head;
}

static void *
list_iterator_get(iterator_t *self) {
    list_iterator_t *itr = (list_iterator_t *) self;

    return itr->node->data;
}

static void
list_iterator_next(iterator_t *self) {
    list_iterator_t *itr = (list_iterator_t *) self;

    itr->node = itr->node->next;
    itr->index++;
}
