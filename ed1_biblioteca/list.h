#ifndef LIST_H
#define LIST_H

#include "base.h"
#include "iterator.h"

typedef struct list_ list_t;


list_t *list_new_full(compare_func_t comparator,
        destroy_func_t destructor);
list_t *list_new(void);


boolean list_insert(list_t *list, int index, void *data);
boolean list_append(list_t *list, void *data);
boolean list_prepend(list_t *list, void *data);

void *list_remove(list_t *list, void *data);
void *list_find(list_t *list, void *data);
void *list_get(list_t *list, int index);
void *list_first(list_t *list);
void *list_last(list_t *list);

iterator_t *list_iterator(list_t *list);

void list_iterate(list_t *list, iterate_func_t itr, void *user_data);

int list_size(list_t *list);
#define list_empty(l) (list_size((l)) == 0)

void list_clear(list_t *list);

void list_delete(list_t *list);

#endif /* LIST_H */
