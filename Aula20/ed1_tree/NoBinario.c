//
// Created by gustavosousa on 04/06/19.
//

#include "NoBinario.h"

NoBinario *
no_binario_novo(void *chave, void *dados, NoBinario *esq, NoBinario *dir) {
    NoBinario *no = malloc(sizeof(NoBinario));
    if (no != NULL) {
        no->chave = chave;
        no->dados = dados;
        no->esq = esq;
        no->dir = dir;
    }
    return no;
}

void
no_binario_libera(NoBinario *no) {
    free(no);
}