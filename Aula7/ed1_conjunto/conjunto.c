#include "conjunto.h"
#include <stdlib.h>
#include <assert.h>

struct conjunto {
    /* elementos da estrutura */
};

conjunto_t *
conjunto_novo(void) {
    /* aloca uma nova estrutura do tipo conjunto_t e inicializa os campos */
    return NULL;
}

conjunto_t *
conjunto_novo_lendo_vetor(int *vetor, size_t qtd) {
    conjunto_t *conj = conjunto_novo();
    if (conj == NULL)
        return NULL;

    for (int i = 0; i < qtd; i++) {
        // Se não consegue adicionar é pq não foi possível alocar memória
        // nesse caso libera o que já foi alocado na chamada conjunto_novo()
        // e retorna NULL
        if (!conjunto_adiciona(conj, vetor[i])) {
            conjunto_libera(conj);
            return NULL;
        }
    }

    return conj;
}


bool
conjunto_contem(conjunto_t *conj, int elemento) {
    /* Percorre o vetor verificando se o elemento já foi incluso */
    return false;
}


bool
conjunto_adiciona(conjunto_t *conj, int elemento) {
    // Antes de tudo a função deve verificar se o elemento já foi adicionado.
    // Para isso é possível utilizar a função conjunto_contem()

    // Em segundo lugar, caso o elemento não tenha sido adicionado, é necessário
    // comparar o tamanho do vetor já alocado com a quantidade de elementos.
    // Se o espaço alocado não for suficiente, a função deve alocar mais memória
    // Para diminuir a complexidade dessa função você pode criar uma função
    // auxiliar encarregada de garantir que a quantidade de memória alocada é
    // suficiente.

    // Por fim, a função deve adicionar o elemento ao vetor


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

/**
  Retorna um novo conjunto cujos elementos são a união entre os conjuntos a e b.
  Retorna NULL se não consegue alocar memória para o novo conjunto
*/
conjunto_t *
conjunto_uniao(conjunto_t *a, conjunto_t *b) {
    conjunto_t *uniao = conjunto_novo();

    // Obtem os elementos do vetor a e adiciona na uniao
    const int *vetor_a = conjunto_vetor(a);
    size_t qtd_a = conjunto_qtd_itens(a);

    for (int i = 0; i < qtd_a; i++) {
        // Se não for possível adicionar um elemento é porque não há memória
        // e portanto deve ser liberada a que já foi alocada
        if (!conjunto_adiciona(uniao, vetor_a[i])) {
            conjunto_libera(uniao);
            return NULL;
        }
    }

    // Faz a mesma coisa para o vetor b
    // Como essas duas partes fazem a mesma coisa, poderiam ser extraídas
    // para uma função
    const int *vetor_b = conjunto_vetor(b);
    size_t qtd_b = conjunto_qtd_itens(b);

    for (int i = 0; i < qtd_b; i++) {
        if (!conjunto_adiciona(uniao, vetor_b[i])) {
            conjunto_libera(uniao);
            return NULL;
        }
    }

    return uniao;
}

bool
conjunto_iguais(conjunto_t *a, conjunto_t *b) {
    // Se os dois conjuntos tem tamanhos diferentes já é possível saber que são
    // diferentes. Em seguida é possível utilizar a função conjunto_contem para
    // verificar se os elementos de um conjunto estão incluídos no outro
    return false;
}

const int *
conjunto_vetor(conjunto_t *conj) {
    return NULL;
}

void
conjunto_libera(conjunto_t *conj) {
}
