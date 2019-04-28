#ifndef PILHA_ENCADEADA_H
#define PILHA_ENCADEADA_H

#include <stdbool.h>

typedef struct pilha Pilha;

Pilha *pilha_nova(void);

void
pilha_empilha(Pilha *pilha, int item);

int
pilha_desempilha(Pilha *pilha);

int
pilha_topo(Pilha *pilha);

bool
pilha_esta_vazia(Pilha *pilha);

void
pilha_libera(Pilha *pilha);

#endif