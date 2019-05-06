//
// Created by gustavo on 03/05/19.
//

#include "lista_ordenada.h"
#include <assert.h>
#include <stdlib.h>


static int
lista_comparacao_direta(const void *a, const void *b) {
    long diff = a - b;
    return diff < 0 ? -1 : diff > 0 ? 1 : 0;
}

lista_t *
lista_nova(lista_comparador_t comparador) {
    lista_t *lista = malloc(sizeof(lista_t));

    lista->cabeca = NULL;
    lista->tamanho = 0;

    if (comparador)
        lista->comparador = comparador;
    else
        lista->comparador = lista_comparacao_direta;

    return lista;
}

void *
lista_obtem(lista_t *lista, size_t posicao) {
    assert(posicao < lista_tamanho(lista));

    lista_no_t *no = lista->cabeca;
    for (int i = 0; i < posicao; i++)
        no = no->proximo;

    return no->item;
}

void *
lista_remove_inicio(lista_t *lista) {
    assert(lista->cabeca != NULL);

    lista_no_t *temp = lista->cabeca;
    lista->cabeca = temp->proximo;
    void *result = temp->item;
    free(temp);

    lista->tamanho--;

    return result;
}

void *
lista_remove(lista_t *lista, size_t posicao) {
    assert(posicao < lista_tamanho(lista));

    if (posicao == 0)
        return lista_remove_inicio(lista);

    lista_no_t *anterior = lista->cabeca;
    for (int i = 1; i < posicao; i++)
        anterior = anterior->proximo;

    lista_no_t *temp = anterior->proximo;
    anterior->proximo = temp->proximo;
    void *result = temp->item;
    free(temp);

    lista->tamanho--;

    return result;
}


static lista_no_t *
lista_no_novo(void *item, lista_no_t *proximo) {
    lista_no_t *no = malloc(sizeof(lista_no_t));
    no->item = item;
    no->proximo = proximo;
    return no;
}

void
lista_adiciona(lista_t *lista, void *item) {
    if (lista->cabeca == NULL || lista->comparador(item, lista->cabeca->item) < 0) {
        lista->cabeca = lista_no_novo(item, lista->cabeca);
    } else {
        lista_no_t *anterior = lista->cabeca;
        while (anterior->proximo != NULL && lista->comparador(item, anterior->proximo->item) > 0)
            anterior = anterior->proximo;

        anterior->proximo = lista_no_novo(item, anterior->proximo);
    }

    lista->tamanho++;
}

void
lista_libera(lista_t *lista) {
    while (!lista_vazia(lista))
        lista_remove_inicio(lista);
    free(lista);
}