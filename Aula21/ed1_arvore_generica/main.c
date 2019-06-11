//
// Created by gustavosousa on 11/06/19.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "conta.h"
#include "str_util.h"
#include "no_lista.h"

#ifdef NDEBUG
#define debug printf
#else
#define debug(...)
#endif

typedef struct arvore NoArvore;
struct arvore {
    void *dados;
    NoArvore *filho, *irmao;
};


NoArvore *
arvore_no_novo(void *dados) {
    NoArvore *arv = malloc(sizeof(NoArvore));
    arv->dados = dados;
    arv->filho = arv->irmao = NULL;
    return arv;
}

void
arvore_no_libera(NoArvore *arv) {
    if (arv->filho)
        arvore_no_libera(arv->filho);

    if (arv->irmao)
        arvore_no_libera(arv->irmao);

    free(arv->dados);
    free(arv);
}

void
percorre_imprime(NoArvore *raiz, NoLista *ancestrais) {
    if (raiz) {
        int nivel = 0;
        NoLista *ult_no = NULL;
        for (NoLista *no = ancestrais; no != NULL; no = no->prox) {
            NoArvore *arv = no->data;
            printf(arv->irmao && nivel != 0 ? "|  " : "   ");
            ult_no = no;
            nivel++;
        }

        NoLista *novo = no_lista_novo(raiz, NULL);
        if (ult_no == NULL)
            ancestrais = novo;
        else
            ult_no->prox = novo;

        Conta *conta = raiz->dados;
        printf(raiz->irmao && nivel != 0 ? "|--" : "\\--");
        printf("%s", conta->nome);

        char saldo[100];
        sprintf(saldo, "%.2lf", conta->saldo);
        int n_spaces = 60 - (nivel + 1) * 3 - strlen(conta->nome) - strlen(saldo);
        while (n_spaces-- > 0)
            printf(" ");

        printf("%s\n", saldo);
        percorre_imprime(raiz->filho, ancestrais);

        NoLista *temp = ancestrais;
        if (ancestrais->prox == NULL)
            ancestrais = NULL;
        else {
            NoLista *no = ancestrais;
            while (temp->prox != NULL) {
                no = temp;
                temp = temp->prox;
            }
            no->prox = NULL;
        }
        free(temp);

        if (nivel != 0)
            percorre_imprime(raiz->irmao, ancestrais);
    }
}


NoArvore *
carrega_contas(FILE *entrada) {
    char buffer[256];
    NoArvore *arv = NULL;

    while (fgets(buffer, 255, entrada)) {
        Conta *conta = conta_le(buffer);
        debug("%s %s %s %.2lf\n", conta->nome, conta->id, conta->id_pai, conta->saldo);


        // TODO: INSERIR A CONTA NA ÁRVORE
    }

    return arv;
}


void
imprime_arvore(NoArvore *arv) {
    percorre_imprime(arv, NULL);
}

NoArvore *
encontra_no_caminho(NoArvore *arv, const char *conta) {
}

void
transfere(NoArvore *arv, const char *de, const char *para, double valor) {
}

double
obtem_saldo(NoArvore *arv, const char *conta) {
}

void
imprime_conta(NoArvore *arv, const char *conta) {
    imprime_arvore(encontra_no_caminho(arv, conta));
}

int main(void) {
    const char *fname = "contas.txt";

    FILE *fp = fopen(fname, "r");
    if (!fp) {
        fprintf(stderr, "Arquivo %s não pode ser aberto", fname);
        return -1;
    }

    NoArvore *arv = carrega_contas(fp);
    imprime_arvore(arv);

//    // Recebimento de salário
//    transfere(arv, "Receitas:Salário", "Ativos:Ativos Atuais:Conta Corrente", 4000);
//
//    // Abastecimento
//    transfere(arv, "Ativos:Ativos Atuais:Conta Corrente", "Despesas:Automovel:Combustivel", 100);
//
//    puts(" ");
//
//    imprime_conta(arv, "Despesas:Automovel");

    return 0;
}
