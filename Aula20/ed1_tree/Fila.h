//
// Created by gustavosousa on 04/06/19.
//

#ifndef ED1_TREE_FILA_H
#define ED1_TREE_FILA_H


#include "No.h"
#include "Base.h"
#include <stdbool.h>

typedef struct {
    No *cauda;
    size_t tam;
} Fila;

#define fila_tam(f) ((f)->tam)
#define fila_vazia(f) ((f)->tam == 0)
#define fila_primeiro(f) ((f)->cauda->prox->dados)

Fila *
fila_nova(void);

void
fila_init(Fila *fila);

bool
fila_adiciona(Fila *fila, void *data);

void *
fila_remove(Fila *fila);

#define fila_libera(f) fila_libera_total((f), NULL)

void
fila_libera_total(Fila *fila, libera_func_t libera);

#endif //ED1_TREE_FILA_H
