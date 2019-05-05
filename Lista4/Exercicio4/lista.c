//
// Created by gustavo on 30/04/19.
//
#include <stdlib.h>
#include <stdbool.h>
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
    NoInt sentinela;    // ponteiro para a cabeça da lista
    size_t qtd;       // qtd de elementos na lista
} ListaInt;

ListaInt *
lista_novo(void) {
    ListaInt *lista = malloc(sizeof(ListaInt));

    lista->sentinela.proximo = &lista->sentinela;
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

    int i = 0;
    NoInt *no = lista->sentinela.proximo;
    while (i < posicao) {
        no = no->proximo;
        i++;
    }

    return no->item;
}

void
lista_adiciona(ListaInt *lista, size_t posicao, int item) {
    NoInt *novo_no = no_int_novo(item, NULL);

    if (posicao > lista->qtd)
        posicao = lista->qtd;

    NoInt *anterior;
    int i = 0;
    anterior = &lista->sentinela;
    while (i < posicao) {
        anterior = anterior->proximo;
        i++;
    }


    novo_no->proximo = anterior->proximo;
    anterior->proximo = novo_no;

    lista->qtd++;
}

void
lista_adiciona_inicio(ListaInt *lista, int item) {
    lista_adiciona(lista, 0, item);
}

void
lista_adiciona_fim(ListaInt *lista, int item) {
    lista_adiciona(lista, lista->qtd, item);
}

int
lista_remove(ListaInt *lista, int posicao) {
    assert(posicao < lista->qtd);

    int i = 0;
    NoInt *anterior = &lista->sentinela;
    while (i < posicao) {
        anterior = anterior->proximo;
        i++;
    }

    NoInt *temp = anterior->proximo;
    int resultado = temp->item;
    anterior->proximo = temp->proximo;

    free(temp);
    lista->qtd--;

    return resultado;
}


int
lista_remove_inicio(ListaInt *lista) {
    return lista_remove(lista, 0);
}

void
lista_libera(ListaInt *lista) {
    while (lista->qtd > 0)
        lista_remove_inicio(lista);
    free(lista);
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