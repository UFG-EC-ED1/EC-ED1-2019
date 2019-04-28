//
// Created by gustavo on 10/04/19.
//

#ifndef ED1_PILHA_H
#define ED1_PILHA_H

#include <stdbool.h>

typedef struct pilha Pilha;

Pilha *
pilha_nova(void);

void
pilha_empilha(Pilha *pilha, void *data);

void *
pilha_topo(Pilha *pilha);

bool
pilha_esta_vazia(Pilha *pilha);

void *
pilha_desempilha(Pilha *pilha);

void
pilha_percorre(Pilha *p, void (funcao)(void *));

void
pilha_libera(Pilha *p);

#endif //ED1_PILHA_H
