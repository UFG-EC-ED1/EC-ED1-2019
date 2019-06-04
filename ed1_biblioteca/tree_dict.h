#ifndef TREE_DICT_H
#define TREE_DICT_H

#include "base.h"
#include "red_black.h"
#include "list.h"


typedef struct tree_dict_entry tree_dict_entry_t;
struct tree_dict_entry {
    const void *key;
    void *value;

    compare_func_t comparator;
};

typedef struct tree_dict tree_dict_t;
struct tree_dict {
    red_black_t *tree;
    compare_func_t key_comparator;
};

tree_dict_t *
tree_dict_new(compare_func_t key_comparator);

boolean
tree_dict_put(tree_dict_t *dict, const void *key, void *data);

tree_dict_entry_t *
tree_dict_get_entry(const tree_dict_t *dict, const void *key);

void *
tree_dict_get(tree_dict_t *dict, const void *key);

boolean
tree_dict_contains(tree_dict_t *dict, const void *key);

void
tree_dict_iterate(tree_dict_t *dict, iterate_entry_func_t iterator, void *user_data);

list_t *
tree_dict_keys(tree_dict_t *dict);

void tree_dict_entry_delete(tree_dict_t *);


#endif //TREE_DICT_H
