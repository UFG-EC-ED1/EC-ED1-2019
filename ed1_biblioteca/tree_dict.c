#include "tree_dict.h"
#include <stdlib.h>


static void
tree_dict_entry_init(tree_dict_entry_t *entry, const void *key, void *data, compare_func_t comparator) {
    entry->key = key;
    entry->value = data;
    entry->comparator = comparator;
}

tree_dict_entry_t *
tree_dict_entry_new(const void *key, void *data, compare_func_t comparator) {
    tree_dict_entry_t *entry = malloc(sizeof(tree_dict_entry_t));
    if (entry)
        tree_dict_entry_init(entry, key, data, comparator);

    return entry;
}

static int
tree_dict_entry_compare(const tree_dict_entry_t *a, const tree_dict_entry_t *b) {
    return a->comparator(a->key, b->key);
}

static int
tree_dict_entry_comparator(const void *a, const void *b) {
    return tree_dict_entry_compare(a, b);
}

tree_dict_t *
tree_dict_new(compare_func_t key_comparator) {
    tree_dict_t *tree_dict = malloc(sizeof(tree_dict_t));
    if (tree_dict) {
        tree_dict->key_comparator = key_comparator;

        tree_dict->tree = red_black_new_full(tree_dict_entry_comparator, NULL, FALSE);
        if (!tree_dict->tree) {
            free(tree_dict);
            return NULL;
        }
    }
    return tree_dict;
}


tree_dict_entry_t *
tree_dict_get_entry(const tree_dict_t *dict, const void *key) {
    tree_dict_entry_t search;
    tree_dict_entry_init(&search, key, NULL, dict->key_comparator);

    return red_black_find(dict->tree, &search);
}


tree_dict_entry_t *
tree_dict_remove_entry(tree_dict_t *dict, const void *key) {
    tree_dict_entry_t search;
    tree_dict_entry_init(&search, key, NULL, dict->key_comparator);

    return red_black_remove(dict->tree, &search);
}

void *
tree_dict_remove(tree_dict_t *dict, const void *key) {
    tree_dict_entry_t *entry = tree_dict_remove_entry(dict, key);
    if (entry == NULL)
        return entry;

    void *result = entry->value;
    free(entry);
    return result;
}

void *
tree_dict_get(tree_dict_t *dict, const void *key) {
    tree_dict_entry_t *node = tree_dict_get_entry(dict, key);

    return node ? node->value : NULL;
}


boolean
tree_dict_contains(tree_dict_t *dict, const void *key) {
    return tree_dict_get_entry(dict, key) != NULL;
}

boolean
tree_dict_put(tree_dict_t *dict, const void *key, void *data) {
    tree_dict_remove(dict, key);
    tree_dict_entry_t *entry = tree_dict_entry_new(key, data, dict->key_comparator);

    return entry ? red_black_insert(dict->tree, entry) : FALSE;
}

int
tree_dict_size(tree_dict_t *dict) {
    return red_black_size(dict->tree);
}


static boolean
tree_dict_entry_copy_key_itr(void *element, void *user_data) {
    tree_dict_entry_t *entry = element;
    list_t *keys = user_data;
    list_append(keys, (void *) entry->key);
    return TRUE;
}

list_t *
tree_dict_keys(tree_dict_t *dict) {
    list_t *result = list_new();
    if (result)
        red_black_inorder(dict->tree, tree_dict_entry_copy_key_itr, result);

    return result;

}