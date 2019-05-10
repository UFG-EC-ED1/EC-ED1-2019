#include "bst.h"

#include <stdlib.h>

typedef struct node_ node_t;
struct node_ {
	void *data;
	node_t *left, *right;
};

static node_t *node_new(void *data, node_t *left, node_t *right) {
	node_t *new_node = malloc(sizeof(node_t));

	return_val_if_fail(new_node, NULL);

	new_node->data = data;
	new_node->left = left;
	new_node->right = right;

	return new_node;
}

struct bst_ {
	compare_func_t cmp;
	node_t *root;
};


bst_t *bst_new(compare_func_t comparator) {
	bst_t *this = malloc(sizeof(bst_t));

	return_val_if_fail(this, NULL);

	this->cmp = comparator ? comparator : general_cmp;

	this->root = NULL;

	return this;
}

static void bst_insert_node(node_t **p_node, node_t *new_node,
		compare_func_t cmp) {
	if (*p_node == NULL) {
		*p_node = new_node;
		return;
	}

	if (cmp(new_node->data, (*p_node)->data) <= 0) {
		bst_insert_node(&(*p_node)->left, new_node, cmp);
	} else {
		bst_insert_node(&(*p_node)->right, new_node, cmp);
	}
}

boolean bst_insert(bst_t *this, void *data) {
	node_t *new_node = node_new(data, NULL, NULL);

	return_val_if_fail(new_node, FALSE);

	bst_insert_node(&this->root, new_node, this->cmp);

	return TRUE;
}

static void *bst_find_node(node_t *root, const void *data,
		compare_func_t cmp) {
	return_val_if_fail(root, NULL);

	if (cmp(data, root->data) == 0) {
		return root->data;
	} else if (cmp(data, root->data) <= 0) {
		return bst_find_node(root->left, data, cmp);
	} else {
		return bst_find_node(root->right, data, cmp);
	}
} 

void *bst_find(bst_t *bst, const void *data) {
	return bst_find_node(bst->root, data, bst->cmp);
}

static void bst_inorder_node(node_t *root, iterate_func_t itr,
		void *user_data) {
	return_if_fail(root);
	bst_inorder_node(root->left, itr, user_data);
	itr(root->data, user_data);
	bst_inorder_node(root->right, itr, user_data);
}
void bst_inorder(bst_t *bst, iterate_func_t itr, void *user_data) {
	bst_inorder_node(bst->root, itr, user_data);
}

static void bst_delete_node(node_t *root, destroy_func_t destructor) {
    if (root) {
        bst_delete_node(root->left, destructor);
        bst_delete_node(root->right, destructor);
        if (destructor)
            destructor(root->data);
        free(root);
    }
}

void bst_delete(bst_t *bst, destroy_func_t destructor) {
    bst_delete_node(bst->root, destructor);
	free(bst);
}

void *bst_remove(bst_t *bst, void *data) {
    node_t **p;


    p = &bst->root;
    while (*p) {
        int cmp = bst->cmp(data, (*p)->data);

        if (cmp < 0) {
            p = &(*p)->left;
        } else if (cmp > 0) {
            p = &(*p)->right;
        } else {
            node_t *n;
            void *result;

            result = (*p)->data;
            if ((*p)->left == NULL) {
                n = *p;
                *p = (*p)->right;
            } else if ((*p)->right == NULL) {
                n = *p;
                *p = (*p)->left;
            } else {    /* (*p)->left != NULL && (*p)->right != NULL */
                node_t **s = &(*p)->right;

                while ((*s)->left) {
                    s = &(*s)->left;
                }
                n = *s;
                (*p)->data = n->data;
                *s = NULL;
            }

            free(n);

            return result;
        }
    }

    return NULL;
}
