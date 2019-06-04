//
// Created by gustavosousa on 04/06/19.
//

#ifndef ED1_TREE_BASE_H
#define ED1_TREE_BASE_H

#include <stdlib.h>

typedef void (*libera_func_t)(void *data);
typedef int (*compara_func_t)(void *a, void *b);

typedef void (*visitor_func_t)(void *item, void *data);


#endif //ED1_TREE_BASE_H
