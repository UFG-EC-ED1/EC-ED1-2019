#ifndef BST_H
#define BST_H

#include "base.h"

/**
 * A binary search tree, can be used to store ordered elements.
 */
typedef struct bst_ bst_t;


/**
 * Creates a new binary search tree..
 * @param comparator function used to define the
 * order of the elements by comparing them.
 * @return a newly allocated bst
 */
bst_t *bst_new(compare_func_t comparator);

/**
 * Adds an element to the tree.
 * @param bst tree
 * @param data data to be inserted
 * @return TRUE if inserted, FALSE otherwise
 */
boolean bst_insert(bst_t *bst, void *data);

/**
 * Finds data stored in the tree.
 * @param bst tree
 * @param data data to be found
 * @return data of the node equal to data,
 * NULL if no node was found
 */
void *bst_find(bst_t *bst, const void *data);

void bst_inorder(bst_t *bst, iterate_func_t itr, void *user_data);

void *bst_remove(bst_t *bst, void *data);

/**
 * Returns the space allocated by bst to the operating
 * system. You can pass a function that will be used to
 * free the data stored in the nodes.
 * @param bst tree
 * @param destructor function to free data
 */
void bst_delete(bst_t *bst, destroy_func_t destructor);

#endif /* BST_H */
