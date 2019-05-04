#include "lista_ordenada.h"
#include <assert.h>
#include <stdlib.h>

int
lista_obtem(lista_t *lista, int posicao) {
    assert(posicao < lista_tamanho(lista));

    lista_no_t *no = lista->cabeca;
    for (int i = 0; i < posicao; i++)
        no = no->proximo;

    return no->item;
}

int
lista_remove_inicio(lista_t *lista) {
    assert(lista->cabeca != NULL);

    lista_no_t *temp = lista->cabeca;
    lista->cabeca = temp->proximo;
    int result = temp->item;
    free(temp);

    lista->tamanho--;

    return result;
}

int
lista_remove(lista_t *lista, size_t posicao) {
    assert(posicao < lista_tamanho(lista));

    if (posicao == 0)
        return lista_remove_inicio(lista);

    lista_no_t *anterior = lista->cabeca;
    for (int i = 1; i < posicao; i++)
        anterior = anterior->proximo;

    lista_no_t *temp = anterior->proximo;
    anterior->proximo = temp->proximo;
    int result = temp->item;
    free(temp);

    lista->tamanho--;

    return result;
}

lista_t *
lista_nova(void) {
    lista_t *lista = malloc(sizeof(lista_t));

    lista->cabeca = NULL;
    lista->tamanho = 0;

    return lista;
}

static lista_no_t *
lista_no_novo(int item, lista_no_t *proximo) {
    lista_no_t *no = malloc(sizeof(lista_no_t));
    no->item = item;
    no->proximo = proximo;
    return no;
}

void
lista_adiciona(lista_t *lista, int item) {
    if (lista->cabeca == NULL || item < lista->cabeca->item) {
        lista->cabeca = lista_no_novo(item, lista->cabeca);
    } else {
        lista_no_t *anterior = lista->cabeca;
        while (anterior->proximo != NULL && item > anterior->proximo->item)
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