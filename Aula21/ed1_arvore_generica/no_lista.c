//
// Created by gustavo on 11/06/19.
//

#include <stdlib.h>
#include "no_lista.h"

NoLista *
no_lista_novo(void *data, NoLista *prox) {
    NoLista *no = malloc(sizeof(NoLista));
    no->data = data;
    no->prox = prox;
    return no;
}