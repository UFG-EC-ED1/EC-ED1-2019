#include "conjunto.h"
#include <stdlib.h>
#include <assert.h>

/**
  Tipo abstrato para manter um conjunto de inteiros
*/
struct conjunto {
    /* elementos da estrutura */
};

conjunto_t *
conjunto_novo(void) {
    return NULL;
}

/**
  Cria um novo conjunto e adiciona os itens do vetor especificado pelos parâmetros vetor e qtd.
  retorna NULL se não consegue alocar memória.
*/
conjunto_t *
conjunto_novo_lendo_vetor(int *vetor, size_t qtd) {
    conjunto_t *conj = conjunto_novo();
    if (conj == NULL)
        return NULL;

    for (int i = 0; i < qtd; i++) {
        if (!conjunto_adiciona(conj, vetor[i])) {
            conjunto_libera(conj);
            return NULL;
        }
    }

    return conj;
}


/**
  Verifica se um conjunto já contem um elemento.
*/
bool
conjunto_contem(conjunto_t *conj, int elemento) {
    return false;
}


bool
conjunto_adiciona(conjunto_t *conj, int elemento) {
    return false;
}


bool
conjunto_remove(conjunto_t *conj, int elemento) {
    return false;
}


size_t
conjunto_qtd_itens(conjunto_t *conj) {
    return 0;
}

/**
  Retorna um novo conjunto cujos elementos são a interseccao entre os conjuntos a e b.
  Retorna NULL se não consegue alocar memória para o novo conjunto
*/
conjunto_t *
conjunto_intersecao(conjunto_t *a, conjunto_t *b) {
    return NULL;
}

static size_t
conjunto_adiciona_vetor(conjunto_t *conj, const int *vetor, size_t qtd) {
    size_t adicionados = 0;

    for (int i = 0; i < qtd; i++) {
        if (conjunto_adiciona(conj, vetor[i]))
            adicionados++;
    }

    return adicionados;
}

/**
  Retorna um novo conjunto cujos elementos são a união entre os conjuntos a e b.
  Retorna NULL se não consegue alocar memória para o novo conjunto
*/
conjunto_t *
conjunto_uniao(conjunto_t *a, conjunto_t *b) {
    conjunto_t *uniao = conjunto_novo();

    if (conjunto_adiciona_vetor(uniao, conjunto_vetor(a), conjunto_qtd_itens(a)) &&
            conjunto_adiciona_vetor(uniao, conjunto_vetor(b), conjunto_qtd_itens(b))) {
        return uniao;
    }

    conjunto_libera(uniao);
    return NULL;
}

/**
  Compara se dois conjuntos são iguais, i.e. contém os mesmos elementos
*/
bool
conjunto_iguais(conjunto_t *a, conjunto_t *b) {
    return false;
}

const int *
conjunto_vetor(conjunto_t *conj) {
    return NULL;
}

/**
  Libera a memória usada no armazenamento do conjunto.
*/
void
conjunto_libera(conjunto_t *conj) {
}