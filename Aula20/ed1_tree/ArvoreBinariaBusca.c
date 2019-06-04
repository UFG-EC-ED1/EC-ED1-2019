//
// Created by gustavosousa on 04/06/19.
//

#include "ArvoreBinariaBusca.h"

ArvoreBinariaBusca *
abb_nova(compara_func_t comparador) {
    ArvoreBinariaBusca *abb = malloc(sizeof(ArvoreBinariaBusca));
    if (abb) {
        abb->comparador = comparador;
    }
    return abb;
}

static int
abb_compara(ArvoreBinariaBusca *abb, void *a, void *b) {
    return abb->comparador != NULL ? abb->comparador(a, b) : a - b;
}


NoBinario **
abb_encontre_no(ArvoreBinariaBusca *abb, NoBinario **raiz, void *chave) {
    NoBinario **no = raiz;

    while (*no != NULL) {
        int cmp = abb_compara(abb, chave, (*no)->chave);
        if (cmp == 0)
            break;
        else if (cmp < 0)
            no = &(*no)->esq;
        else
            no = &(*no)->dir;
    }

    return no;
}

NoBinario *
abb_encontre(ArvoreBinariaBusca *abb, void *chave) {
    return *abb_encontre_no(abb, &abb->raiz, chave);
}


bool
abb_insere(ArvoreBinariaBusca *abb, void *chave, void *dados) {
    NoBinario *novo = no_binario_novo(chave, dados, NULL, NULL);
    if (novo == NULL)
        return false;

    NoBinario **to_insert = abb_encontre_no(abb, &abb->raiz, chave);
    *to_insert = novo;

    return true;
}


static NoBinario **
abb_max(NoBinario **raiz) {
    while ((*raiz)->dir)
        raiz = &(*raiz)->dir;

    return raiz;
}

NoBinario *
abb_remove_no(NoBinario **to_remove) {
    NoBinario *result = *to_remove;

    if (!result->esq)
        *to_remove = result->dir;
    else if (!result->dir)
        *to_remove = result->esq;
    else {
        NoBinario **max_ptr = abb_max(&result->esq);
        NoBinario *max = abb_remove_no(max_ptr);
        *to_remove = max;
    }


    return result;
}

NoBinario *
abb_remove(ArvoreBinariaBusca *abb, void *chave) {
    NoBinario **to_remove = abb_encontre_no(abb, &abb->raiz, chave);
    return *to_remove != NULL ? abb_remove_no(to_remove) : NULL;
}


static void
abb_libera_no(NoBinario *raiz) {
    if (raiz->esq != NULL) {
        abb_libera_no(raiz->esq);
        raiz->esq = NULL;
    }

    if (raiz->dir != NULL) {
        abb_libera_no(raiz->dir);
        raiz->dir = NULL;
    }

    no_binario_libera(raiz);
}

void
abb_libera(ArvoreBinariaBusca *abb) {

}
