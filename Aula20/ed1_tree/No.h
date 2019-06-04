//
// Created by gustavosousa on 04/06/19.
//

#ifndef ED1_TREE_NO_H
#define ED1_TREE_NO_H

#include <stdlib.h>

typedef struct no No;
struct no {
    void *dados;
    No *prox;
};

No *
no_novo(void *dados, No *prox);

void
no_libera(No *node);

#endif //ED1_TREE_NO_H
