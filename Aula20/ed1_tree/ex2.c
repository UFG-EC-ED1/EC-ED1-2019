//
// Created by gustavo on 04/06/19.
//

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct no No;
struct no {
    void *dados;
    No *prox;
};


No *
no_novo(void *dados, No *prox) {
    No *no = malloc(sizeof(No));
    if (no) {
        no->dados = dados;
        no->prox = prox;
    }

    return no;
}

typedef struct {
    No *cauda;
    size_t tam;
} Fila;

#define fila_tam(f) ((f)->tam)
#define fila_vazia(f) (fila_tam((f)) == 0)
#define fila_primeiro(f) ((f)->cauda->prox->dados)

void
fila_init(Fila *fila) {
    if (fila) {
        fila->tam = 0;
        fila->cauda = NULL;
    }
}

Fila *
fila_nova(void) {
    Fila *fila = malloc(sizeof(fila));
    fila_init(fila);
    return fila;
}


bool
fila_adiciona(Fila *fila, void *data) {
    No *novo = no_novo(data, NULL);
    if (novo == NULL)
        return false;

    if (fila->cauda == NULL) {
        fila->cauda = novo;
        novo->prox = novo;
    } else {
        novo->prox = fila->cauda->prox;
        fila->cauda = novo;
    }

    fila->tam++;

    return true;
}

void *
fila_remove(Fila *fila) {
    assert(fila->tam > 0);
    No *cabeca = fila->cauda->prox;

    if (fila->tam == 1)
        fila->cauda = NULL;
    else
        fila->cauda->prox = cabeca->prox;

    fila->tam--;

    void *result = cabeca->dados;
    free(cabeca);

    return result;
}


typedef struct ab_no NoArvBin;
struct ab_no {
    int chave;
    NoArvBin *esq, *dir;
};


NoArvBin *
ab_no_novo(int chave) {
    NoArvBin *no = malloc(sizeof(NoArvBin));

    no->chave = chave;
    no->esq = no->dir = NULL;

    return no;
}

NoArvBin *
ab_no_encontra(NoArvBin *raiz, int chave) {
    if (raiz == NULL)
        return NULL;

    if (raiz->chave == chave)
        return raiz;

    NoArvBin *esq = ab_no_encontra(raiz->esq, chave);
    if (esq != NULL)
        return esq;

    return ab_no_encontra(raiz->dir, chave);
}

NoArvBin *
ab_insere_no(NoArvBin *raiz, NoArvBin *no) {
    if (!raiz) {
        return no;
    }

    Fila *f = fila_nova();
    fila_adiciona(f, raiz);

    while (!fila_vazia(f)) {
        NoArvBin *pai = fila_remove(f);
        if (pai->esq == NULL) {
            pai->esq = no;
            break;
        } else {
            fila_adiciona(f, pai->esq);
        }

        if (pai->dir == NULL) {
            pai->dir = no;
            break;
        } else {
            fila_adiciona(f, pai->dir);
        }
    }

//    while (!fila_vazia(f))
//        fila_remove(f);
//    free(f);

    return raiz;
}

bool
ab_eh_de_busca(NoArvBin *raiz) {

}

int
main(void) {
    NoArvBin *raiz = NULL;
    for (int i = 1; i < 9; i++)
        raiz = ab_insere_no(raiz, ab_no_novo(i));

    assert(!ab_eh_de_busca(raiz));


//    int seq[] = {10, 5, 15, 3, 7, 12, 17};
//    NoArvBin *raizB = NULL;
//    for (int i = 0; i < 7; i++)
//        raizB = ab_insere_no(raizB, ab_no_novo(seq[i]));
//
//    assert(ab_eh_de_busca(raizB));

}