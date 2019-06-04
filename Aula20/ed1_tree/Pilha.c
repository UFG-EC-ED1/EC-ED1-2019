//
// Created by gustavosousa on 04/06/19.
//

#include "Pilha.h"
#include "Base.h"

#include <assert.h>

Pilha *
pilha_nova(void) {
    Pilha *pilha = malloc(sizeof(pilha));
    if (pilha != NULL) {
        pilha->tam = 0;
        pilha->topo = NULL;
    }
    return pilha;
}

bool
pilha_push(Pilha *pilha, void *dados) {
    No *novo = no_novo(dados, pilha->topo);
    if (novo == NULL)
        return false;

    pilha->topo = novo;
    pilha->tam++;

    return true;
}

void *
pilha_pop(Pilha *pilha) {
    assert(!pilha_vazia(pilha));

    No *topo = pilha->topo;
    pilha->topo = topo->prox;
    pilha->tam--;

    void *result = topo->dados;
    no_libera(topo);

    return result;
}

void
pilha_libera(Pilha *pilha, libera_func_t libera) {
    while (!pilha_vazia(pilha)) {
        void *topo = pilha_pop(pilha);
        if (libera != NULL)
            libera(topo);
    }
    free(pilha);
}