#include <stdio.h>
#include <assert.h>
#include "pilha_encadeada.h"
#include "expressao_bem_formada.h"

int main() {
    Pilha *pilha = pilha_nova();

    assert(pilha_esta_vazia(pilha));


    pilha_empilha(pilha, 10);
    assert(10 == pilha_topo(pilha));
    assert(!pilha_esta_vazia(pilha));
    assert(10 == pilha_desempilha(pilha));
    assert(pilha_esta_vazia(pilha));

    pilha_empilha(pilha, 1);
    assert(1 == pilha_topo(pilha));
    pilha_empilha(pilha, 2);
    assert(2 == pilha_desempilha(pilha));
    assert(1 == pilha_desempilha(pilha));

    pilha_libera(pilha);

    assert(expressao_bem_formada("{X * [(X + Y) / (J - 3)] + Y}"));
    assert(!expressao_bem_formada("{X * [(X + Y) / (J - 3)} + Y}"));

    return 0;
}