//
// Created by gustavo on 03/05/19.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lista_ordenada.h"
#include "aluno.h"

static int
compara_str(const void *a, const void *b) {
    return strcmp(a, b);
}

static void
test_string() {
    lista_t *lista = lista_nova(compara_str);

    lista_adiciona(lista, "Fulano");
    lista_adiciona(lista, "Ciclano");
    lista_adiciona(lista, "Beltrano");

    assert(3 == lista_tamanho(lista));
    assert(0 == strcmp("Beltrano", lista_obtem(lista, 0)));
    assert(0 == strcmp("Ciclano", lista_obtem(lista, 1)));
    assert(0 == strcmp("Fulano", lista_obtem(lista, 2)));

    for (lista_no_t *no = lista->cabeca; no; no = no->proximo)
        printf("%s\n", (char *) no->item);

    lista_libera(lista);
}

static int
compara_aluno_nome(const void *a, const void *b) {
    aluno_t *aa = (aluno_t *) a;
    aluno_t *ab = (aluno_t *) b;
    return strcmp(aa->nome, ab->nome);
}

static int
compara_aluno_nota(const void *a, const void *b) {
    double diff = aluno_calcula_media((aluno_t *) a) - aluno_calcula_media((aluno_t *) b);
    if (diff < 0)
        return -1;
    else if (diff > 0)
        return 1;
    else
        return 0;
}


static void
test_aluno() {
    aluno_t *fulano = aluno_novo("Fulano", 5, 5, 2);
    aluno_t *ciclano = aluno_novo("Ciclano", 8, 7, 6);
    aluno_t *beltrano = aluno_novo("Beltrano", 8, 4, 5);

    // -------- Ordenado por nome
    lista_t *lista = lista_nova(compara_aluno_nome);
    lista_adiciona(lista, fulano);
    lista_adiciona(lista, ciclano);
    lista_adiciona(lista, beltrano);

    for (lista_no_t *no = lista->cabeca; no; no = no->proximo) {
        aluno_imprime(no->item, stdout);
    }

    assert(0 == strcmp("Beltrano", ((aluno_t *) lista_obtem(lista, 0))->nome));
    assert(0 == strcmp("Ciclano", ((aluno_t *) lista_obtem(lista, 1))->nome));
    assert(0 == strcmp("Fulano", ((aluno_t *) lista_obtem(lista, 2))->nome));

    lista_libera(lista);

    puts("--------------------");

    // -------- Ordenado por nota

    lista = lista_nova(compara_aluno_nota);
    lista_adiciona(lista, fulano);
    lista_adiciona(lista, ciclano);
    lista_adiciona(lista, beltrano);

    for (lista_no_t *no = lista->cabeca; no; no = no->proximo) {
        aluno_imprime(no->item, stdout);
    }

    assert(0 == strcmp("Fulano", ((aluno_t *) lista_obtem(lista, 0))->nome));
    assert(0 == strcmp("Beltrano", ((aluno_t *) lista_obtem(lista, 1))->nome));
    assert(0 == strcmp("Ciclano", ((aluno_t *) lista_obtem(lista, 2))->nome));

    lista_libera(lista);

    aluno_libera(fulano);
    aluno_libera(beltrano);
    aluno_libera(ciclano);
}

int
main(void) {
    test_string();
    test_aluno();

    return 0;
}