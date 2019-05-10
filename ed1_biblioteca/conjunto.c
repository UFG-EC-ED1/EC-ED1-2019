#include "conjunto.h"
#include <stdlib.h>

/**
  Estrutura para manter um conjunto de inteiros
*/
struct conjunto {
    int *elementos; // ponteiro para o inicio do vetor de elementos
    size_t tamanho;     // tamanho alocado para o vetor de elementos

    size_t qtd;     // quantidade de elementos inseridos
};


#define CONJUNTO_VETOR_TAM_INICIAL 50
#define CONJUNTO_VETOR_FATOR_AUMENTO 1.5

// Redimensiona o tamanho do vetor de elementos
static bool
conjunto_redimensiona_vetor(conjunto_t *conj, size_t novo_tamanho) {
    int *novo_elementos = realloc(conj->elementos, sizeof(int) * novo_tamanho);

    if (novo_elementos == NULL)
        return false;

    conj->elementos = novo_elementos;
    conj->tamanho = novo_tamanho;

    return true;
}

// Verifica se o vetor de elementos tem espaço para um elemento na posicao
// e redimensiona se necessario usando a funcao conjunto_redimensiona_vetor()
static bool
conjunto_vetor_cabe(conjunto_t *conj, size_t posicao) {
    if (posicao < conj->tamanho)
        return true; // posicao já cabe no vetor alocado

    // calcula novo  tamanho
    size_t novo_tamanho = conj->tamanho == 0
                          ? CONJUNTO_VETOR_TAM_INICIAL
                          : conj->tamanho * CONJUNTO_VETOR_FATOR_AUMENTO;

    return conjunto_redimensiona_vetor(conj, novo_tamanho);
}

// Verifica se ha memoria alocada em excesso e libera
static void
conjunto_libera_desnecessario(conjunto_t *conj) {
    size_t tam_reduzido = conj->tamanho / CONJUNTO_VETOR_FATOR_AUMENTO;
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
        conj->tamanho = 0;
        conj->elementos = NULL;
    }

    return conj;
}

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
    return conj->qtd;
}

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
    return conj->elementos;
}

void
conjunto_libera(conjunto_t *conj) {
    if (conj->elementos != NULL)
        free(conj->elementos);

    free(conj);
}