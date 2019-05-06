//
// Created by gustavo on 03/05/19.
//

#ifndef ED1_GENERICO_LISTA_ORDENADA_H
#define ED1_GENERICO_LISTA_ORDENADA_H

#include <stdlib.h>

typedef struct lista_no lista_no_t;
struct lista_no {
    void *item;
    lista_no_t *proximo;
};

typedef int (*lista_comparador_t)(const void *, const void *);

typedef struct {
    lista_no_t *cabeca;
    size_t tamanho;

    lista_comparador_t comparador;
} lista_t;

#define lista_tamanho(l) ((l)->tamanho)
#define lista_vazia(l) ((l)->tamanho == 0)
#define lista_no_inicio(l) ((l)->cabeca)

lista_t *
lista_nova(lista_comparador_t comparador);

void
lista_adiciona(lista_t *lista, void *item);

void *
lista_obtem(lista_t *lista, size_t posicao);

void *
lista_remove_inicio(lista_t *lista);

void *
lista_remove(lista_t *lista, size_t posicao);

void
lista_libera(lista_t *lista);


#endif //ED1_GENERICO_LISTA_ORDENADA_H
