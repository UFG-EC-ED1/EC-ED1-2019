//
// Created by gustavo on 05/05/19.
//


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

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

typedef struct lista_int {
    NoInt *cauda;     // ponteiro para ultimo elemento
    size_t qtd;       // qtd de elementos na lista
} ListaInt;


ListaInt *
lista_novo(void) {
    ListaInt *lista = malloc(sizeof(ListaInt));

    lista->cauda = NULL;
    lista->qtd = 0;

    return lista;
}


size_t
lista_tamanho(ListaInt *lista) {
    return lista->qtd;
}


int
lista_obtem(ListaInt *lista, size_t posicao) {
    assert(posicao < lista->qtd);

    NoInt *no = lista->cauda->proximo;
    for (int i = 0; i < posicao; i++)
        no = no->proximo;

    return no->item;
}

void
lista_adiciona(ListaInt *lista, size_t posicao, int item) {
    NoInt *novo_no = no_int_novo(item, NULL);

    if (posicao > lista->qtd)
        posicao = lista->qtd;

    if (lista->cauda == NULL) {
        lista->cauda = novo_no;
        novo_no->proximo = lista->cauda;
    } else if (posicao == lista->qtd) {
        novo_no->proximo = lista->cauda->proximo;
        lista->cauda->proximo = novo_no;
        lista->cauda = novo_no;
    } else {
        NoInt *anterior = lista->cauda;
        for (int i = 0; i < posicao; i++) {
            anterior = anterior->proximo;
        }

        novo_no->proximo = anterior->proximo;
        anterior->proximo = novo_no;
    }

    lista->qtd++;
}

void
lista_adiciona_fim(ListaInt *lista, int item) {
    lista_adiciona(lista, lista->qtd, item);
}

void
lista_adiciona_inicio(ListaInt *lista, int item) {
    lista_adiciona(lista, 0, item);
}

int
lista_remove(ListaInt *lista, int posicao) {
    assert(posicao < lista->qtd);

    NoInt *anterior = lista->cauda;
    for (int i = 0; i < posicao; i++) {
        anterior = anterior->proximo;
    }

    NoInt *temp = anterior->proximo;
    anterior->proximo = temp->proximo;

    int resultado = temp->item;
    free(temp);

    lista->qtd--;

    if (lista->qtd == 0)
        lista->cauda = NULL;
    else if (lista->cauda == temp) {
        lista->cauda = anterior;
    }

    return resultado;
}

int
lista_remove_inicio(ListaInt *lista) {
    return lista_remove(lista, 0);
}

int
main(void) {
    int i;

    ListaInt *lista = lista_novo();
    lista_adiciona_fim(lista, 10);
    lista_adiciona_fim(lista, 20);
    lista_adiciona(lista, 10, 30); // adiciona fim
    lista_adiciona_inicio(lista, 5);

    assert(4 == lista_tamanho(lista));

    i = 0;
    assert(5 == lista_obtem(lista, i++));
    assert(10 == lista_obtem(lista, i++));
    assert(20 == lista_obtem(lista, i++));
    assert(30 == lista_obtem(lista, i++));

    assert(30 == lista_remove(lista, 3));
    assert(3 == lista_tamanho(lista));

    lista_adiciona(lista, 3, 20);
    assert(4 == lista_tamanho(lista));

    assert(20 == lista_remove(lista, 3));
    assert(3 == lista_tamanho(lista));

    assert(5 == lista_remove(lista, 0));
    assert(10 == lista_remove_inicio(lista));
    assert(1 == lista_tamanho(lista));

    puts("[OK] Todos os testes");
}