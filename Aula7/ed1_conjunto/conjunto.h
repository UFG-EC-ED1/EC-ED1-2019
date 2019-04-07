#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <stdlib.h>
#include <stdbool.h>

/**
  Tipo abstrato para manter um conjunto de inteiros
*/
typedef struct conjunto conjunto_t;

/**
 * Cria um novo conjunto vazio
 * @return um ponteiro para um novo conjunto ou NULL se não foi possívelalocar memória
 */
conjunto_t *
conjunto_novo(void);

/**
 * Cria um novo conjunto e adiciona os itens de um vetor
 * @param vetor vetor contendo os itens a serem adicionados
 * @param qtd tamanho do vetor
 * @return um ponteiro para um novo conjunto ou NULL se não foi possívelalocar memória
 */
conjunto_t *
conjunto_novo_lendo_vetor(int *vetor, size_t qtd);


/**
 * Verifica se um conjunto já contem um elemento.
 * @param conjunto conjunto
 * @param elemento elemento
 * @return true se o elemento pertence ao conjunto
 */
bool
conjunto_contem(conjunto_t *conjunto, int elemento);

/**
 * Adiciona um elemento ao conjunto.
 * @param conjunto conjunto
 * @param elemento elemento a ser adicionado
 * @return false se houve um problema ao alocar memória, true se o elemento já
           pertence ou foi incluído com sucesso
 */
bool
conjunto_adiciona(conjunto_t *conjunto, int elemento);

/**
 * Remove um elemento do conjunto
 * @param conjunto conjunto
 * @param elemento inteiro a ser removido
 * @return true se o elemento pertence ao conjunto
 */
bool
conjunto_remove(conjunto_t *conjunto, int elemento);


/**
 * Retorna a quantidade de elementos em um conjunto
 * @param conjunto
 * @return a quantidade de elementos do conjunto
 */
size_t
conjunto_qtd_itens(conjunto_t *conjunto);

/**
 * Retorna um novo conjunto cujos elementos são a interseccao entre os conjuntos a e b.
 * @param a conjunto a
 * @param b conjunto b
 * @return um ponteiro para o novo conjunto alocado, NULL se não for possível alocar memória
 */
conjunto_t *
conjunto_intersecao(conjunto_t *a, conjunto_t *b);


/**
 * Retorna um novo conjunto cujos elementos são a união entre os conjuntos a e b.
 * @param a conjunto a
 * @param b conjunto b
 * @return um ponteiro para o novo conjunto alocado, NULL se não for possível alocar memória
 */
conjunto_t *
conjunto_uniao(conjunto_t *a, conjunto_t *b);

/**
 * Compara se dois conjuntos são iguais, i.e. contém os mesmos elementos
 * @param a conjunto a
 * @param b conjunto b
 * @return true se os dois conjuntos contém os mesmos elementos
 */
bool
conjunto_iguais(conjunto_t *a, conjunto_t *b);


/**
 * Retorna um vetor contendo os elementos do conjunto para permitir que os
 * elemento sejam percorridos
 * @param conjunto
 * @return
 */
const int *
conjunto_vetor(conjunto_t *conjunto);

/**
 * Libera a memória usada no armazenamento do conjunto.
 * @param conjunto
 */
void
conjunto_libera(conjunto_t *conjunto);

#endif
