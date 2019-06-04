//
// Created by gustavosousa on 04/06/19.
//

#ifndef ED1_TREE_NO_BINARIO_H
#define ED1_TREE_NO_BINARIO_H

#include "Base.h"

typedef struct no_binario NoBinario;
struct no_binario {
    void *chave;
    void *dados;
    NoBinario *esq, *dir;
};


NoBinario *
no_binario_novo(void *chave, void *dados, NoBinario *esq, NoBinario *dir);

void
no_binario_libera(NoBinario *no);

#endif //ED1_TREE_NO_BINARIO_H
