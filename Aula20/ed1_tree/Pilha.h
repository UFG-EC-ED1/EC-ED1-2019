//
// Created by gustavosousa on 04/06/19.
//

#ifndef ED1_TREE_PILHA_H
#define ED1_TREE_PILHA_H

#include "No.h"
#include "Base.h"
#include <stdbool.h>

typedef struct pilha {
    No *topo;
    size_t tam;
} Pilha;

#define pilha_topo(p) ((p)->topo->dados)
#define pilha_vazia(p) ((p)->topo == NULL)
#define pilha_tam(p) ((p)->tam)


Pilha *
pilha_nova(void);

bool
pilha_push(Pilha *pilha, void *dados);

void *
pilha_pop(Pilha *pilha);

void
pilha_libera(Pilha *pilha, libera_func_t libera);

#endif //ED1_TREE_PILHA_H
