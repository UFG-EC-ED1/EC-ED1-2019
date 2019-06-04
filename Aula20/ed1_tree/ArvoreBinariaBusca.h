//
// Created by gustavosousa on 04/06/19.
//

#ifndef ED1_TREE_ARVORE_BINARIA_BUSCA_H
#define ED1_TREE_ARVORE_BINARIA_BUSCA_H

#include "NoBinario.h"
#include "Base.h"
#include "Pilha.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    NoBinario *raiz;
    compara_func_t comparador;
} ArvoreBinariaBusca;


ArvoreBinariaBusca *abb_nova(compara_func_t comparador);

bool abb_insere(ArvoreBinariaBusca *abb, void *chave, void *dados);

NoBinario *abb_remove(ArvoreBinariaBusca *abb, void *chave);

void abb_libera(ArvoreBinariaBusca *abb);

#endif //ED1_TREE_ARVORE_BINARIA_BUSCA_H
