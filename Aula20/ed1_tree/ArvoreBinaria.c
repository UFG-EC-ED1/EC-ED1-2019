//
// Created by gustavosousa on 04/06/19.
//
#include "ArvoreBinaria.h"
#include "Fila.h"

NoBinario *
ab_insere(NoBinario *raiz, NoBinario *no) {
    if (!raiz) {
        return no;
    }

    Fila *f = fila_nova();
    fila_adiciona(f, raiz);

    while (!fila_vazia(f)) {
        NoBinario *pai = fila_remove(f);
        if (pai->esq == NULL) {
            pai->esq = no;
            break;
        } else {
            fila_adiciona(f, pai->esq);
        }

        if (pai->dir == NULL) {
            pai->dir = no;
            break;
        } else {
            fila_adiciona(f, pai->dir);
        }
    }

    fila_libera(f);

    return raiz;
}


void
ab_emordem(NoBinario *raiz, visitor_func_t visitor, void *data) {
    if (raiz) {
        ab_emordem(raiz->esq, visitor, data);
        visitor(raiz, data);
        ab_emordem(raiz->dir, visitor, data);
    }
}