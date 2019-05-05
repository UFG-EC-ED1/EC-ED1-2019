#ifndef LISTA_ORDENADA_H
#define LISTA_ORDENADA_H

#include <stdlib.h>

typedef struct lista_no lista_no_t;
struct lista_no {
    int item;
    lista_no_t *proximo;
};

typedef struct {
    lista_no_t sentinela;
    size_t tamanho;
} lista_t;

#define lista_cabeca(l) ((l)->sentinela.proximo)
#define lista_tamanho(l) ((l)->tamanho)
#define lista_vazia(l) ((l)->tamanho == 0)
#define lista_no_inicio(l) ((l)->cabeca)

lista_t *
lista_nova(void);

void
lista_adiciona(lista_t *lista, int item);

int
lista_obtem(lista_t *lista, int posicao);

int
lista_remove_inicio(lista_t *lista);

int
lista_remove(lista_t *lista, size_t posicao);

void
lista_libera(lista_t *lista);

#endif //LISTA_ORDENADA_H
