//
// Created by gustavosousa on 04/06/19.
//

#include <assert.h>
#include "Fila.h"

#define fila_cabeca(f) ((f)->cauda ? (f)->cauda->prox : NULL)

Fila *
fila_nova(void) {
    Fila *fila = malloc(sizeof(fila));
    fila_init(fila);
    return fila;
}


void
fila_init(Fila *fila) {
    if (fila) {
        fila->tam = 0;
        fila->cauda = NULL;
    }
}

bool
fila_adiciona(Fila *fila, void *data) {
    No *novo = no_novo(data, fila_cabeca(fila));
    if (novo == NULL)
        return false;

    if (fila->cauda == NULL) {
        fila->cauda = novo;
    }

    fila->cauda->prox = novo;
    fila->cauda = novo;
    fila->tam++;

    return true;
}

void *
fila_remove(Fila *fila) {
    No *cabeca = fila->cauda->prox;

    if (fila->tam == 1)
        fila->cauda = NULL;
    else
        fila->cauda = fila->cauda->prox;

    fila->tam--;

    void *result = cabeca->dados;
    no_libera(cabeca);

    return result;
}

void
fila_libera_total(Fila *fila, libera_func_t libera) {
    while (!fila_vazia(fila)) {
        void *dados = fila_remove(fila);
        if (libera)
            libera(dados);
    }
    free(fila);
}