//
// Created by gustavo on 10/04/19.
//
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Pilha.h"

typedef struct pilha_no PilhaNo;
struct pilha_no {
    void *item;
    PilhaNo *prox;
};


PilhaNo *
pilha_no_novo(void *item, PilhaNo *prox) {
    PilhaNo *no = malloc(sizeof(PilhaNo));
    no->item = item;
    no->prox = prox;
    return no;
}

struct pilha {
    PilhaNo *topo;
};


Pilha *
pilha_nova(void) {
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

void
pilha_empilha(Pilha *pilha, void *item) {
    pilha->topo = pilha_no_novo(item, pilha->topo);
}

void *
pilha_desempilha(Pilha *pilha) {
    assert(pilha->topo != NULL);

    PilhaNo *temp = pilha->topo;
    pilha->topo = temp->prox;

    void *item = temp->item;
    free(temp);

    return item;
}

bool
pilha_esta_vazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

void
pilha_percorre(Pilha *p, void (funcao)(void *)) {
    for (PilhaNo *no = p->topo; no != NULL; no = no->prox)
        funcao(no->item);
}

void
pilha_libera(Pilha *p) {
    free(p);
}