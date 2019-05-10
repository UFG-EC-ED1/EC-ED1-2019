#include "stack.h"

#include <stdlib.h>

typedef struct node_ node_t;
struct node_ {
	void *data;
	node_t *next;
};
static node_t *node_new(void *data, node_t *next) {
	node_t *new_node = malloc(sizeof(node_t));

	return_val_if_fail(new_node, NULL);

	new_node->data = data;
	new_node->next = next;

	return new_node;
}

struct stack_ {
	node_t *top;
};

stack_t *stack_new(void) {
	stack_t *this = malloc(sizeof(stack_t));

	return_val_if_fail(this, NULL);

	this->top = NULL;

	return this;
}

boolean stack_push(stack_t *this, void *data) {
	node_t *new_node = node_new(data, this->top);

	return_val_if_fail(new_node, FALSE);
	
	this->top = new_node;
	
	return TRUE;
}

boolean stack_empty(stack_t *this) {
	return_val_if_fail(this->top, TRUE);

	return FALSE;
}

void *stack_top(stack_t *this) {
	return_val_if_fail(!stack_empty(this), NULL);

	return this->top->data;
}

void *stack_pop(stack_t *this) {
	node_t *pop_node;
	void *pop_data;

	return_val_if_fail(!stack_empty(this), NULL);

	pop_node = this->top;
	this->top = this->top->next;	/* removes the node */

	pop_data = pop_node->data;

	free(pop_node);		/* free the removed node */

	return pop_data;
}

void stack_delete(stack_t *this) {
	while (stack_pop(this));

	free(this);
}
