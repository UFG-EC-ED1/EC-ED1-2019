//
// Created by gustavo on 11/06/19.
//

#ifndef ED1_ARVORE_GENERICA_NO_LISTA_H
#define ED1_ARVORE_GENERICA_NO_LISTA_H

typedef struct no_lista NoLista;
struct no_lista {
    void *data;
    NoLista *prox;
};

NoLista *
no_lista_novo(void *data, NoLista *prox);

#endif //ED1_ARVORE_GENERICA_NO_LISTA_H
