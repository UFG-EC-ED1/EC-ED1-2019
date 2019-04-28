//
// Created by gustavo on 26/04/19.
//

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct pilha_vetor PilhaVetor;
struct pilha_vetor {
    int *vetor; //ponteiro do vetor
    size_t max;  // tamanho do vetor alocado
    size_t topo; // vazia = 0
};

bool
pilha_vetor_empilha(PilhaVetor *pilha, int item) {
    if (pilha->topo == pilha->max) {
        size_t new_max = pilha->max == 0 ? 10 : pilha->max * 1.5;
        int *new_vetor = realloc(pilha->vetor, new_max);

        if (!new_vetor)
            return false;

        pilha->vetor = new_vetor;
        pilha->max = new_max;
    }

    assert(pilha->topo < pilha->max);

    pilha->vetor[pilha->topo] = item;
    pilha->topo++;
}

int
pilha_vetor_desempilha(PilhaVetor *pilha) {
    assert(pilha->topo > 0);

    pilha->topo--;
    return pilha->vetor[pilha->topo];
}

int
pilha_vetor_topo(PilhaVetor *pilha) {
    assert(pilha->topo > 0);

    return pilha->vetor[pilha->topo - 1];
}

bool
pilha_vetor_esta_vazia(PilhaVetor *pilha) {
    return pilha->topo == 0;
}