#include "conjunto.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

static void
init_vetor_aleatorio(int *itens, size_t qtd) {
    for (int i = 0; i < qtd; i++)
        itens[i] = rand() % qtd;
}


static void
print_conjunto(conjunto_t *conj) {
    const int *vetor = conjunto_vetor(conj);
    size_t n = conjunto_qtd_itens(conj);

    for (int i = 0; i < n; i++)
        printf("%d ", vetor[i]);
    puts("");
}

static void
test_conjunto_novo(void) {
    conjunto_t *conjunto = conjunto_novo();
    assert(conjunto != NULL);
    assert(0 == conjunto_qtd_itens(conjunto));

    int vetor_inicial[] = { 2, 5, 2, 3, 4, 3 };
    conjunto = conjunto_novo_lendo_vetor(vetor_inicial, 6);
    assert(4 == conjunto_qtd_itens(conjunto));

    conjunto_libera(conjunto);
}

static void
test_conjunto_contem(void) {
    conjunto_t *conj = conjunto_novo();

    int itens[1024];
    init_vetor_aleatorio(itens, 1024);

    for (int i = 0; i < 1024; i++) {
        conjunto_adiciona(conj, itens[i]);
        assert(conjunto_contem(conj, itens[i]));
    }

    for (int i = 0; i < 1024; i++) {
        assert(conjunto_contem(conj, itens[i]));
    }

    for (int i = 0; i < 1024; i++) {
        conjunto_remove(conj, itens[i]);
        assert(!conjunto_contem(conj, itens[i]));
    }

    conjunto_libera(conj);
}


static void
test_conjunto_adiciona_remove(void) {
    conjunto_t *conj = conjunto_novo();

    conjunto_adiciona(conj, 10);
    assert(conjunto_contem(conj, 10));

    conjunto_adiciona(conj, 20);
    assert(conjunto_contem(conj, 20));

    assert(!conjunto_contem(conj, 15));
    assert(2 == conjunto_qtd_itens(conj));

    assert(!conjunto_remove(conj, 15));
    assert(2 == conjunto_qtd_itens(conj));

    assert(conjunto_remove(conj, 10));
    assert(1 == conjunto_qtd_itens(conj));

    assert(!conjunto_remove(conj, 10));
    assert(1 == conjunto_qtd_itens(conj));

    assert(conjunto_remove(conj, 20));
    assert(0 == conjunto_qtd_itens(conj));

    conjunto_libera(conj);
}

static void
test_conjunto_iguais(void) {
    int itens[1024];
    init_vetor_aleatorio(itens, 1024);

    conjunto_t *a = conjunto_novo_lendo_vetor(itens, 1024);
    conjunto_t *b = conjunto_novo();
    for (int i = 1024 - 1; i >= 0; i--)
        conjunto_adiciona(b, itens[i]);

    assert(conjunto_iguais(a, b));

    conjunto_libera(a);
    conjunto_libera(b);

    a = conjunto_novo();
    conjunto_adiciona(a, 10);
    conjunto_adiciona(a, 10);
    conjunto_adiciona(a, 20);
    conjunto_adiciona(a, 30);

    b = conjunto_novo();
    conjunto_adiciona(b, 20);
    conjunto_adiciona(b, 30);
    conjunto_adiciona(b, 20);
    conjunto_adiciona(b, 10);

    assert(conjunto_iguais(a, b));

    conjunto_libera(a);
    conjunto_libera(b);
}

static void
test_conjunto_interseccao(void) {
    int itens_a[] = { 10, 20, 30, 40, 50 };
    conjunto_t *a = conjunto_novo_lendo_vetor(itens_a, 5);

    int itens_b[] = { 10, 30, 50, 60, 70 };
    conjunto_t *b = conjunto_novo_lendo_vetor(itens_b, 5);

    conjunto_t *c = conjunto_intersecao(a, b);
    assert(3 == conjunto_qtd_itens(c));
    assert(conjunto_contem(c, 10));
    assert(conjunto_contem(c, 30));
    assert(conjunto_contem(c, 50));

    conjunto_libera(a);
    conjunto_libera(b);
    conjunto_libera(c);
}

static void
test_conjunto_uniao(void) {
    int itens_a[] = { 10, 20, 30, 40, 50 };
    conjunto_t *a = conjunto_novo_lendo_vetor(itens_a, 5);

    int itens_b[] = { 10, 30, 50, 60, 70 };
    conjunto_t *b = conjunto_novo_lendo_vetor(itens_b, 5);

    conjunto_t *c = conjunto_uniao(a, b);
    assert(7 == conjunto_qtd_itens(c));
    assert(conjunto_contem(c, 10));
    assert(conjunto_contem(c, 20));
    assert(conjunto_contem(c, 30));
    assert(conjunto_contem(c, 40));
    assert(conjunto_contem(c, 50));
    assert(conjunto_contem(c, 60));
    assert(conjunto_contem(c, 70));

    conjunto_libera(a);
    conjunto_libera(b);
    conjunto_libera(c);
}


int
main(void) {
    test_conjunto_novo();
    test_conjunto_contem();
    test_conjunto_adiciona_remove();
    test_conjunto_iguais();
    test_conjunto_interseccao();
    test_conjunto_uniao();
}