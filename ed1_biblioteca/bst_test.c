#include "bst.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int bst_strcmp(const void *a, const void *b) {
	return strcmp((const char *) a, (const char *) b);
}

static boolean bst_inorder_itr(void *data, void *user_data) {
    static char *str = NULL;

    if (str != NULL) {
        assert(bst_strcmp(str, data) <= 0);
        assert(bst_strcmp(data, str) >= 0);
    }

    str = data;

	return TRUE;
}

int main() {
	bst_t *bst;

	assert(bst = bst_new(bst_strcmp));
	assert(bst_insert(bst, "hello"));
	assert(bst_insert(bst, "world"));
	assert(bst_insert(bst, "abacaxi"));
	assert(bst_insert(bst, "tosco"));

    assert(strcmp(bst_remove(bst, "hello"), "hello") == 0);
    assert(bst_remove(bst, "hello") == NULL);

	bst_inorder(bst, bst_inorder_itr, NULL);

	bst_delete(bst, NULL);

	return 0;
}
