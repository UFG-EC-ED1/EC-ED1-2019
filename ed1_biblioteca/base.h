#ifndef BASE_H
#define BASE_H

/**
 * Checks for the truth of an expression b, and returns if it's false.
 * Used in void functions.
 */
#define return_if_fail(b) if(!(b))return

/**
 * Check for the truth of an expression b, and returns a value v, if it's
 * false.
 * Used in functions that return a value.
 */
#define return_val_if_fail(b, v) if(!(b))return(v)


/**
 * Boolean type definition.
 */
typedef int boolean;
#define FALSE 0
#define TRUE (!FALSE)

/**
 * Comparator function, should return less than 0 if
 * a < b, 0 if a = b and a number greater than 0 if a > b
 */
typedef int (*compare_func_t)(const void *a, const void *b);

/**
 * A direct compare function. May be used for numeric data.
 * @param a
 * @param b
 * @return an integer less than 0 if a < b, 0 if a = b and an
 * integer greater than 0 if a > b
 */
int general_cmp(const void *a, const void *b);

typedef boolean (*iterate_func_t)(void *value, void *user_data);
typedef boolean (*iterate_entry_func_t)(void *key, void *value, void *user_data);

typedef void (*destroy_func_t)(void *);

void stub_destructor(void *);

#endif /* BASE_H */
