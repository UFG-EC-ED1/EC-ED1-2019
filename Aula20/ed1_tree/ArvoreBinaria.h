//
// Created by gustavosousa on 04/06/19.
//

#ifndef ED1_TREE_ARVORE_BINARIA_H
#define ED1_TREE_ARVORE_BINARIA_H

#include <stdbool.h>
#include "NoBinario.h"

NoBinario *
ab_insere(NoBinario *raiz, NoBinario *no);

void
ab_emordem(NoBinario *raiz, visitor_func_t visitor, void *data);


#endif //ED1_TREE_ARVORE_BINARIA_H
