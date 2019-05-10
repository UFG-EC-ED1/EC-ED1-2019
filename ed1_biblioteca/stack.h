#ifndef STACK_H
#define STACK_H

#include "base.h"


/* A stack that where data can be pushed. */
typedef struct stack_ stack_t;

/**
 * Creates a new stack.
 * @return a newly allocated stack structure.
 */
stack_t *stack_new(void);

/**
 * Pushes elements an element on the top of the stack.
 * @param stack stack to push the element
 * @param data data element to be pushed
 * @return TRUE if data was pushed, FALSE otherwise
 */
boolean stack_push(stack_t *stack, void *data);

/**
 * Removes an element from the top of the stack.
 * @param stack stack to pop the element from
 * @return data stored at the top of the stack or NULL if
 * the stack is empty
 */
void *stack_pop(stack_t *stack);

/**
 * Peeks the element on the top of the stack.
 * @param stack stack from which to look for the element
 * @return data at the top of the stack or NULL
 * if the stack is empty
 */
void *stack_top(stack_t *stack);

/**
 * Checks if a stack is empty.
 * @param stack stack to be checked
 * @return TRUE if it's empty, FALSE otherwise
 */
boolean stack_empty(stack_t *stack);


/**
 * Free data space used by a stack. If any data elements
 * stored in the stack need to be also freed, it must be
 * done by the user.
 * @param stack stack to be freed
 */
void stack_delete(stack_t *stack);


#endif /* STACK_H */
