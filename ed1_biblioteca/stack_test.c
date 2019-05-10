#include "stack.h"

#include <assert.h>

int main() {
	stack_t *stack;
	
	assert(stack = stack_new());

	assert(stack_empty(stack));
	
	/* Asserting the pushes just to detect errors easily,
	 * if one assert returned false and we didn't take note of it
	 * we may waste time thinking there's something going wrong.
	 * The same idea is valid for the assert on stack_new() */
	assert(stack_push(stack, (void *) 10));

	assert(!stack_empty(stack));

	assert(stack_top(stack) == (void *) 10);

	assert(stack_pop(stack) == (void *) 10);
	
	assert(stack_empty(stack));

	assert(stack_push(stack, (void *) 20));

	assert(stack_push(stack, (void *) 30));

	assert(stack_pop(stack) == (void *) 30);
	
	assert(!stack_empty(stack));

	assert(stack_pop(stack) == (void *) 20);
	
	assert(stack_empty(stack));

	stack_delete(stack);
	
	return 0;
}
