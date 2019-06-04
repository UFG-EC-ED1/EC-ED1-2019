//
// Created by gustavo on 04/06/19.
//

#include <assert.h>
#include <stdio.h>
#include "ArvoreBinariaBusca.h"
#include "ArvoreBinaria.h"



static void
array_append(void *item, void *data) {
    NoBinario *no = item;
    int *counter = data;
    int *saida = counter + 1;

    saida[*counter] = (int) no->chave;
    *counter = *counter + 1;
}

int
main(void) {
    ArvoreBinariaBusca *abb = abb_nova(NULL);
    abb_insere(abb, (void *) 5, NULL);
    abb_insere(abb, (void *) 4, NULL);
    abb_insere(abb, (void *) 3, NULL);
    abb_insere(abb, (void *) 6, NULL);
    abb_insere(abb, (void *) 10, NULL);
    abb_insere(abb, (void *) 7, NULL);
    abb_insere(abb, (void *) 8, NULL);
    abb_insere(abb, (void *) 1, NULL);
    abb_insere(abb, (void *) 2, NULL);
    abb_insere(abb, (void *) 9, NULL);

    int saida[11];
    saida[0] = 0;

    ab_emordem(abb->raiz, array_append, saida);

    for (int i = 1; i <= 10; i++) {
        assert(saida[i] == i);
    }
}