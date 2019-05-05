#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct no_int NoInt;
struct no_int {
    int item;
    NoInt *proximo;
};

NoInt *
no_int_novo(int item, NoInt *proximo) {
    NoInt *no = malloc(sizeof(NoInt));

    no->item = item;
    no->proximo = proximo;

    return no;
}

NoInt *
no_int_adiciona_inicio(NoInt *cabeca, int item) {
    return no_int_novo(item, cabeca);
}

NoInt *
no_int_adiciona_fim(NoInt *cabeca, int item) {
    if (cabeca == NULL)
        return no_int_adiciona_inicio(cabeca, item);

    NoInt *no = cabeca;

    while (no->proximo != NULL)
        no = no->proximo;

    no->proximo = no_int_novo(item, NULL);

    return cabeca;
}

NoInt *
no_int_adiciona(NoInt *cabeca, int posicao, int item) {
    if (cabeca == NULL || posicao == 0)
        return no_int_adiciona_inicio(cabeca, item);

    NoInt *no = cabeca;

    while (no->proximo != NULL && --posicao > 0)
        no = no->proximo;

    no->proximo = no_int_novo(item, no->proximo);

    return cabeca;
}

NoInt *
no_int_remove_inicio(NoInt *cabeca) {
    if (cabeca == NULL)
        return NULL;

    NoInt *temp = cabeca;
    cabeca = cabeca->proximo;
    free(temp);

    return cabeca;
}

size_t
no_int_tamanho(NoInt *cabeca) {
    if (cabeca == NULL)
        return 0;

    return 1 + no_int_tamanho(cabeca->proximo);
}

NoInt *
no_int_obtem(NoInt *cabeca, int posicao) {
    int i = 0;
    NoInt *no = cabeca;
    while (no != NULL && i < posicao) {
        no = no->proximo;
        i++;
    }

    return no;
}


NoInt *
no_int_obtem_recursivo(NoInt *cabeca, int posicao) {
    if (posicao == 0)
        return cabeca;

    return no_int_obtem_recursivo(cabeca->proximo, posicao - 1);
}

NoInt *
no_int_inverte(NoInt *cabeca) {
    NoInt *nova_cabeca = NULL;

    while (cabeca != NULL) {
        NoInt *proximo = cabeca->proximo;

        cabeca->proximo = nova_cabeca;
        nova_cabeca = cabeca;

        cabeca = proximo;
    }

    return nova_cabeca;
}

NoInt *
no_int_filtro(NoInt *cabeca, int valor_filtrado) {
    NoInt *nova_cabeca = NULL;
    NoInt *nova_cauda = NULL;   // Mantém um ponteiro pra cauda para adicionar facilmente no fim da lista

    for (NoInt *no = cabeca; no != NULL; no = no->proximo) {
        if (no->item != valor_filtrado) {
            NoInt *novo_no = no_int_novo(no->item, NULL);

            if (nova_cabeca == NULL) { // se é o primeiro item a ser adicionado
                nova_cabeca = nova_cauda = novo_no;
            } else {
                nova_cauda->proximo = novo_no;
                nova_cauda = novo_no;
            }
        }
    }

    return nova_cabeca;
}

NoInt *
no_int_filtro_recursivo(NoInt *cabeca, int valor_filtrado) {
    if (cabeca == NULL)
        return NULL;

    NoInt *proximo = no_int_filtro_recursivo(cabeca->proximo, valor_filtrado);

    if (cabeca->item == valor_filtrado)
        return proximo;
    else
        return no_int_novo(cabeca->item, proximo);
}

void
no_int_libera_lista(NoInt *cabeca) {
    while (cabeca)
        cabeca = no_int_remove_inicio(cabeca);
}

void
no_int_libera_lista_recursivo(NoInt *cabeca) {
    if (cabeca != NULL) {
        no_int_libera_lista(cabeca->proximo);
        free(cabeca);
    }
}


static void
test_filtro() {
    int vetor[] = {10, 2, 3, 10, 2, 4};
    NoInt *lista = NULL; // Cria uma nova lista vazia
    for (int i = 0; i < 6; i++)
        lista = no_int_adiciona_fim(lista, vetor[i]);
    for (int i = 0; i < 6; i++)
        assert(vetor[i] == no_int_obtem(lista, i)->item);

    NoInt *lista_filtrada = no_int_filtro(lista, 2);
    assert(4 == no_int_tamanho(lista_filtrada));

    no_int_libera_lista(lista);
    no_int_libera_lista(lista_filtrada);
}

static void
test_filtro_recursivo() {
    int vetor[] = {10, 2, 3, 10, 2, 4};
    NoInt *lista = NULL; // Cria uma nova lista vazia
    for (int i = 0; i < 6; i++)
        lista = no_int_adiciona_fim(lista, vetor[i]);
    for (int i = 0; i < 6; i++)
        assert(vetor[i] == no_int_obtem(lista, i)->item);

    NoInt *lista_filtrada = no_int_filtro_recursivo(lista, 2);
    assert(4 == no_int_tamanho(lista_filtrada));

    no_int_libera_lista_recursivo(lista);
    no_int_libera_lista_recursivo(lista_filtrada);
}

int
main(void) {
    NoInt *lista = NULL; // lista vazia

    assert(0 == no_int_tamanho(lista));
    assert(NULL == no_int_obtem(lista, 0));

    lista = no_int_adiciona_inicio(lista, 1);
    assert(1 == no_int_obtem(lista, 0)->item);
    lista = no_int_adiciona_inicio(lista, 2);
    lista = no_int_adiciona_inicio(lista, 3);
    assert(3 == no_int_tamanho(lista));

    // Como sempre adicionamos no inicio, o primeiro
    // item deve ser o último que foi adicionado
    assert(3 == no_int_obtem(lista, 0)->item);
    assert(2 == no_int_obtem(lista, 1)->item);
    assert(1 == no_int_obtem(lista, 2)->item);

    // Como há apenas 3 elementos (0-2), a partir da posicao 3
    // o resultado deve ser NULL
    assert(NULL == no_int_obtem(lista, 3));
    assert(NULL == no_int_obtem(lista, 10));

    // Adiciona um item em uma posição específica
    lista = no_int_adiciona(lista, 2, 4);
    assert(4 == no_int_tamanho(lista));
    assert(4 == no_int_obtem(lista, 2)->item);


    lista = no_int_inverte(lista);

    // Verifica o resultado da função inverte
    assert(1 == no_int_obtem(lista, 0)->item);
    assert(4 == no_int_obtem(lista, 1)->item);
    assert(2 == no_int_obtem(lista, 2)->item);
    assert(3 == no_int_obtem(lista, 3)->item);

    no_int_libera_lista(lista);


    test_filtro();
    test_filtro_recursivo();

    return 0;
}
