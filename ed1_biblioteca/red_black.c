#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "red_black.h"


typedef enum { RED, BLACK } color_t;

typedef struct red_black_node_ red_black_node_t;
struct red_black_node_ {
    red_black_node_t *parent;
    red_black_node_t *left, *right;
    color_t color;
    void *data;
};

static red_black_node_t NULL_NODE_ = {
    NULL, &NULL_NODE_, &NULL_NODE_, BLACK, NULL
};
#define NULL_NODE (&NULL_NODE_)

struct red_black_ {
    red_black_node_t *root;
    compare_func_t compare;
    destroy_func_t destroy;
    boolean repeated;
    int size;
};

static void rotate_left(red_black_t *self, red_black_node_t *node);
static void rotate_right(red_black_t *self, red_black_node_t *node);


#define GRANDPARENT(n) ((n)->parent->parent)

red_black_t *
red_black_new_full(compare_func_t compare,
                   destroy_func_t destroy,
                   boolean repeated)
{
    red_black_t *self;

    self = malloc(sizeof(red_black_t));

    return_val_if_fail(self != NULL, NULL);

    self->root = NULL_NODE;
    self->size = 0;
    self->compare = compare ? compare : general_cmp;
    self->destroy = destroy;
    self->repeated = repeated;

    return self;
}

red_black_t *
red_black_new(void)
{
    return red_black_new_full(NULL, NULL, TRUE);
}


int
red_black_size(red_black_t *rb) {
    return rb->size;
}

compare_func_t
red_black_set_compare(red_black_t *self, compare_func_t compare)
{
    compare_func_t old_compare = self->compare;

    self->compare = compare;

    return old_compare;
}


static red_black_node_t *
red_black_find_node(red_black_node_t *root, const void *data,
		compare_func_t compare) {
    red_black_node_t *node;
	int cmp;

    for (node = root; node != NULL_NODE; /* */) {
	    cmp	= compare(data, node->data);

	    if (cmp < 0) {
            node = node->left;
        } else if (cmp == 0) {
            return node;
        } else {
            node = node->right;
        }
    }

    return NULL_NODE;
}

void *
red_black_find(red_black_t *self, const void *data)
{
	red_black_node_t *node;
	
	node = red_black_find_node(self->root, data, self->compare);

	return node == NULL_NODE ? NULL : node->data;
}

static void
red_black_remove_update_color(red_black_t *self, red_black_node_t *x) {
    /* Based on Introduction to Algorithms, by Cormen et al */
    while (x != self->root && x->color == BLACK) {
        if (x == x->parent->left) {
            red_black_node_t *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_left(self, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotate_right(self, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotate_left(self, x->parent);
                x = self->root;
            }
        } else {
            assert(x == x->parent->right);
            red_black_node_t *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_right(self, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotate_left(self, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotate_right(self, x->parent);
                x = self->root;
            }
        }
    }

    x->color = BLACK;
}


void *
red_black_remove(red_black_t *self, void *data)
{
	red_black_node_t *node, *x, *y;
	void *result;

	node = red_black_find_node(self->root, data, self->compare);

	if (node == NULL_NODE)
		return NULL;

	result = node->data;

    
	if (node->left == NULL_NODE || node->right == NULL_NODE) {
        y = node;
    } else { /* node->left != NULL && node->right != NULL */
        y = node->right;

        while (y->left != NULL_NODE) {
            y = y->left;
        }
    }


    x = (y->left != NULL_NODE ? y->left : y->right);

    x->parent = y->parent;

    if (y->parent == NULL_NODE) {
        self->root = x;
    } else  if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        assert(y == y->parent->right);
        y->parent->right = x;
    }

    if (y != node) {
        node->data = y->data;
    }

    if (y->color == BLACK) {
        red_black_remove_update_color(self, x);
    }

    free(y);

    self->size--;

    return result;
}

boolean
red_black_insert(red_black_t *self, void *data)
{
    red_black_node_t *parent, *node, **p;

    parent = NULL_NODE;
    p = &self->root;

    while (*p != NULL_NODE) {
        int cmp = self->compare(data, (*p)->data);

        parent = *p;

        if (cmp < 0) {
            p = &(*p)->left;
        } else if (cmp == 0) {
            if (self->repeated) {
                p = &(*p)->left;
            } else {
                return TRUE;
            }
        } else {
            p = &(*p)->right;
        }
    }

    assert(*p == self->root || parent != NULL_NODE);
    assert(*p == NULL_NODE);

    node = malloc(sizeof(red_black_node_t));

    return_val_if_fail(node != NULL, FALSE);

    *p = node;

    node->parent = parent;
    node->left = node->right = NULL_NODE;

    node->data = data;
    node->color = RED;

    /* Based on Introduction to Algorithms, by Cormen et al */
    while (node != self->root && node->parent->color == RED) {
        if (node->parent == GRANDPARENT(node)->left) {
            red_black_node_t *tmp = GRANDPARENT(node)->right;
            if (tmp->color == RED) {
                node->parent->color = BLACK;
                tmp->color = BLACK;
                GRANDPARENT(node)->color = RED;
                node = GRANDPARENT(node);
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotate_left(self, node);
                }

                node->parent->color = BLACK;
                GRANDPARENT(node)->color = RED;
                rotate_right(self, GRANDPARENT(node));
            }
        } else {
            assert(node->parent == GRANDPARENT(node)->right);
            red_black_node_t *tmp = GRANDPARENT(node)->left;
            if (tmp->color == RED) {
                node->parent->color = BLACK;
                tmp->color = BLACK;
                GRANDPARENT(node)->color = RED;
                node = GRANDPARENT(node);
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotate_right(self, node);
                }

                node->parent->color = BLACK;
                GRANDPARENT(node)->color = RED;
                rotate_left(self, GRANDPARENT(node));
            }
        }
    }

    self->root->color = BLACK;
    self->size++;

    return TRUE;
}
static void
red_black_inorder_recur(red_black_node_t *root,
                        iterate_func_t itr,
                        void *user_data)
{
    if (root != NULL_NODE) {
        red_black_inorder_recur(root->left, itr, user_data);
        itr(root->data, user_data);
        red_black_inorder_recur(root->right, itr, user_data);
    }
}
void
red_black_inorder(red_black_t *self,
                  iterate_func_t itr,
                  void *user_data)
{
    red_black_inorder_recur(self->root, itr, user_data);
}

static void
red_black_delete_node(red_black_node_t *root, destroy_func_t destroy)
{
    if (root != NULL_NODE) {
        red_black_delete_node(root->left, destroy);
        red_black_delete_node(root->right, destroy);
        if (destroy)
            destroy(root->data);
        free(root);
    }
}

void
red_black_clear(red_black_t *self)
{
    red_black_delete_node(self->root, self->destroy);
    self->root = NULL_NODE;
    self->size = 0;
}

void
red_black_delete(red_black_t *self)
{
    red_black_clear(self);
    free(self);
}
        
static void
rotate_left(red_black_t *self, red_black_node_t *node)
{
    red_black_node_t *tmp;

    if (node == NULL_NODE || node->right == NULL_NODE)
        return;

    tmp = node->right;

    node->right = tmp->left;
    if (tmp->left != NULL_NODE)
        tmp->left->parent = node;

    tmp->parent = node->parent;
    
    if (node->parent == NULL_NODE) {
        self->root = tmp;
    } else if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        assert(node->parent->right == node);
        node->parent->right = tmp;
    }

    tmp->left = node;
    node->parent = tmp;
}

static void
rotate_right(red_black_t *self, red_black_node_t *node)
{
    red_black_node_t *tmp;

    if (node == NULL_NODE || node->left == NULL_NODE)
        return;

    tmp = node->left;
    
    node->left = tmp->right;
    if (tmp->right != NULL_NODE)
        tmp->right->parent = node;

    tmp->parent = node->parent;

    if (node->parent == NULL_NODE) {
        self->root = tmp;
    } else if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        assert(node->parent->right == node);
        node->parent->right = tmp;
    }

    tmp->right = node;
    node->parent = tmp;
}
