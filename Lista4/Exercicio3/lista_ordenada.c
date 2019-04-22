#include "lista_ordenada.h"
#include <assert.h>
#include <stdlib.h>

int
lista_obtem(lista_t *lista, int posicao) {
    assert(posicao < lista_tamanho(lista));

    lista_no_t *no = lista->cabeca;
    while (posicao-- > 0)
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
    while (--posicao > 0)
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

void
lista_adiciona(lista_t *lista, int item);

void
lista_libera(lista_t *lista);