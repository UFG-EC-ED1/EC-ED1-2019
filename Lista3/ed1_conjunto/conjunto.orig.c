#include "conjunto.h"
#include <stdlib.h>
#include <assert.h>

/**
  Estrutura para manter um conjunto de inteiros
*/
struct conjunto {
    int *elementos; // ponteiro para o inicio do vetor de elementos
    size_t tam;     // tamanho alocado para o vetor de elementos

    size_t qtd;     // quantidade de elementos inseridos
};


#define CONJUNTO_VETOR_TAM_INICIAL 50
#define CONJUNTO_VETOR_FATOR_AUMENTO 1.5

// Redimensiona o tamanho do vetor de elementos
static bool
conjunto_redimensiona_vetor(conjunto_t *conj, size_t novo_tam) {
    int *novo_elementos = realloc(conj->elementos, sizeof(int) * novo_tam);

    if (novo_elementos == NULL)
        return false;

    conj->elementos = novo_elementos;
    conj->tam = novo_tam;

    return true;
}

// Verifica se o vetor de elementos tem espaço para um elemento na posicao
// e redimensiona se necessario usando a funcao conjunto_redimensiona_vetor()
static bool
conjunto_vetor_cabe(conjunto_t *conj, size_t posicao) {
    assert(posicao <= conj->tam);

    if (posicao < conj->tam)
        return true; // posicao já cabe no vetor alocado

    // calcula novo  tamanho
    size_t novo_tamanho = conj->tam == 0
                          ? CONJUNTO_VETOR_TAM_INICIAL
                          : conj->tam * CONJUNTO_VETOR_FATOR_AUMENTO;
    assert(novo_tamanho > posicao);

    return conjunto_redimensiona_vetor(conj, novo_tamanho);
}

// Verifica se ha memoria alocada em excesso e libera
void
conjunto_libera_desnecessario(conjunto_t *conj) {
    size_t tam_reduzido = conj->tam / CONJUNTO_VETOR_FATOR_AUMENTO;
    if (tam_reduzido > conj->qtd)
        conjunto_redimensiona_vetor(conj, tam_reduzido);
}


/**
 * Cria um novo conjunto e aloca o vetor de elementos com um tamanho
 * prédefinido
 */
conjunto_t *
conjunto_novo_aloca(size_t tam) {
    conjunto_t *conj = conjunto_novo();

    if (conj == NULL)
        return NULL;

    if (!conjunto_redimensiona_vetor(conj, tam)) {
        conjunto_libera(conj);
        return NULL;
    }

    return conj;
}

conjunto_t *
conjunto_novo(void) {
    conjunto_t *conj = malloc(sizeof(conjunto_t));

    if (conj != NULL) {
        conj->qtd = 0;
        conj->tam = 0;
        conj->elementos = NULL;
    }

    return conj;
}

/**
  Cria um novo conjunto e adiciona os itens do vetor especificado pelos parâmetros vetor e qtd.
  retorna NULL se não consegue alocar memória.
*/
conjunto_t *
conjunto_novo_lendo_vetor(int *vetor, size_t qtd) {
    conjunto_t *conj = conjunto_novo_aloca(qtd);
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


/*
 * Função auxiliar que obtem a posição no vetor onde o elemento se encontra ou
 * -1 case o elemento não seja encontrado
 */
static int
conjunto_encontra_item(conjunto_t *conj, int elemento) {
    assert(conj);
    for (int i = 0; i < conj->qtd; i++)
        if (conj->elementos[i] == elemento)
            return i;

    return -1;
}


bool
conjunto_contem(conjunto_t *conj, int elemento) {
    return conjunto_encontra_item(conj, elemento) != -1;
}


bool
conjunto_adiciona(conjunto_t *conj, int elemento) {
    if (conjunto_contem(conj, elemento))
        return true;

    if (!conjunto_vetor_cabe(conj, conj->qtd))
        return false;

    conj->elementos[conj->qtd] = elemento;
    conj->qtd++;

    return true;
}


bool
conjunto_remove(conjunto_t *conj, int elemento) {
    int i = conjunto_encontra_item(conj, elemento);
    if (i < 0)
        return false;

    conj->qtd--;
    conj->elementos[i] = conj->elementos[conj->qtd];

    conjunto_libera_desnecessario(conj);

    return true;
}


size_t
conjunto_qtd_itens(conjunto_t *conj) {
    assert(conj != NULL);
    return conj->qtd;
}

/**
  Retorna um novo conjunto cujos elementos são a interseccao entre os conjuntos a e b.
  Retorna NULL se não consegue alocar memória para o novo conjunto
*/
conjunto_t *
conjunto_intersecao(conjunto_t *a, conjunto_t *b) {
    conjunto_t *intersect = conjunto_novo_lendo_vetor(a->elementos, a->qtd);

    if (intersect == NULL)
        return NULL;

    for (int i = 0; i < intersect->qtd; i++) {
        if (!conjunto_contem(b, intersect->elementos[i]))
            conjunto_remove(intersect, intersect->elementos[i]);
    }

    return intersect;
}

/**
  Retorna um novo conjunto cujos elementos são a união entre os conjuntos a e b.
  Retorna NULL se não consegue alocar memória para o novo conjunto
*/
conjunto_t *
conjunto_uniao(conjunto_t *a, conjunto_t *b) {
    conjunto_t *uniao = conjunto_novo_aloca(conjunto_qtd_itens(a) + conjunto_qtd_itens(b));

    if (uniao == NULL)
        return NULL;

    for (int i = 0; i < a->qtd; i++)
        conjunto_adiciona(uniao, a->elementos[i]);

    for (int i = 0; i < b->qtd; i++)
        conjunto_adiciona(uniao, b->elementos[i]);

    return uniao;
}

/**
  Compara se dois conjuntos são iguais, i.e. contém os mesmos elementos
*/
bool
conjunto_iguais(conjunto_t *a, conjunto_t *b) {
    if (a->qtd != b->qtd)
        return false;

    for (int i = 0; i < a->qtd; i++) {
        if (!conjunto_contem(b, a->elementos[i]))
            return false;
    }

    return true;
}

const int *
conjunto_vetor(conjunto_t *conj) {
    assert(conj != NULL);

    return conj->elementos;
}

/**
  Libera a memória usada no armazenamento do conjunto.
*/
void
conjunto_libera(conjunto_t *conj) {
    assert(conj != NULL);
    assert(conj->elementos == NULL || conj->tam > 0);

    if (conj->elementos != NULL)
        free(conj->elementos);

    free(conj);
}