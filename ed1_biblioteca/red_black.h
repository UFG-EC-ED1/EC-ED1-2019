#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "base.h"

typedef struct red_black_ red_black_t;

red_black_t *
red_black_new_full(compare_func_t comparator,
                   destroy_func_t destructor,
                   boolean repeated);


red_black_t *
red_black_new(void);

boolean
red_black_insert(red_black_t *rb, void *data);

void *
red_black_find(red_black_t *rb, const void *data);

void *
red_black_remove(red_black_t *rb, void *data);

void
red_black_inorder(red_black_t *rb, iterate_func_t itr, void *user_data);

void
red_black_clear(red_black_t *rb);

void
red_black_delete(red_black_t *rb);

int
red_black_size(red_black_t *rb);

compare_func_t
red_black_set_compare(red_black_t *rb, compare_func_t compare);


#endif /* RED_BLACK_TREE_H */
