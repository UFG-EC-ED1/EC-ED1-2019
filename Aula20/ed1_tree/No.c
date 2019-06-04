//
// Created by gustavosousa on 04/06/19.
//

#include "No.h"

No *
no_novo(void *dados, No *prox) {
    No *no = malloc(sizeof(No));
    if (no) {
        no->dados = dados;
        no->prox = prox;
    }

    return no;
}

void
no_libera(No *no) {
    free(no);
}