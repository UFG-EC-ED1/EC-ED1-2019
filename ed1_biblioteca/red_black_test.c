#include "red_black.h"

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int red_black_strcmp(const void *a, const void *b) {
	return strcmp((const char *) a, (const char *) b);
}

static boolean red_black_inorder_itr(void *data, void *user_data) {
    static char *str = NULL;

    if (str != NULL) {
        assert(red_black_strcmp(str, data) <= 0);
        assert(red_black_strcmp(data, str) >= 0);
    }

    str = data;

	return TRUE;
}

int main() {
	red_black_t *rb;

	assert(rb = red_black_new_full(red_black_strcmp, NULL, TRUE));
	assert(0 == red_black_size(rb));
	assert(red_black_insert(rb, "hello"));
	assert(red_black_insert(rb, "world"));
	assert(red_black_insert(rb, "abacaxi"));
	assert(red_black_insert(rb, "tosco"));
	assert(4 == red_black_size(rb));

    assert(strcmp(red_black_remove(rb, "hello"), "hello") == 0);
    assert(red_black_remove(rb, "hello") == NULL);
	assert(3 == red_black_size(rb));

	red_black_inorder(rb, red_black_inorder_itr, NULL);
	assert(3 == red_black_size(rb));


	red_black_delete(rb);

	return 0;
}
