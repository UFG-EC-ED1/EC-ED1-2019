#include <stdio.h>
#include <assert.h>
#include "lista_ordenada.h"

int main() {
    lista_t *lista = lista_nova();
    assert(0 == lista_tamanho(lista));

    int vetor[] = {10, 2, 5, 3, 1, 4, 10, 20, 2, 3};
    const int tam_vetor = 10;

    for (int i = 0; i < tam_vetor; i++) {
        lista_adiciona(lista, vetor[i]);
        assert(i + 1 == lista_tamanho(lista));
    }

    lista_no_t *no = lista->cabeca;
    while (no != NULL && no->proximo != NULL) {
        assert(no->item <= no->proximo->item);
        no = no->proximo;
    }

    for (int i = 0; i < tam_vetor; i++) {
        lista_remove(lista, lista_tamanho(lista) / 2);
        assert(tam_vetor - i - 1 == lista_tamanho(lista));
    }




    lista_libera(lista);

    return 0;
}