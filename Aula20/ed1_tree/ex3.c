//
// Created by gustavo on 04/06/19.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Pilha.h"

typedef enum {
    OPERANDO, OPERADOR
} TipoElemento;

typedef struct {
    TipoElemento tipo;
    int valor;
} ElemExpr;

typedef struct ab_no NoArvBin;
struct ab_no {
    ElemExpr *elemento;
    NoArvBin *esq, *dir;
};

NoArvBin *ab_no_novo(TipoElemento tipo, int valor, NoArvBin *left, NoArvBin *right) {
    NoArvBin *no = malloc(sizeof(NoArvBin));
    no->elemento = malloc(sizeof(ElemExpr));
    no->elemento->tipo = tipo;
    no->elemento->valor = valor;
    no->esq = left;
    no->dir = right;
    return no;
}

static bool
eh_digito(char ch) {
    return ch >= '0' && ch <= '9';
}

static bool
eh_letra(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

static int
le_numero(const char *str, int *start) {
    int i = *start;
    while (eh_digito(str[i]))
        i++;

    int result = strtol(str + *start, NULL, 10);
    *start = i - 1;

    return result;
}

static char *
le_var(const char *str, int *start) {
    int i = *start;
    while (eh_letra(str[i]) || eh_digito(str[i]))
        i++;

    char *result = malloc(sizeof(char) * (i + 1));
    strncpy(result, str, i);
    *start = *start + i;

    return result;
}

static int
prioridade_operador(char ch) {
    return ch == '/' || ch == '*';
}

NoArvBin *
parse_expressao(const char *infix) {
    Pilha *pilha = pilha_nova();
    Pilha *saida = pilha_nova();

    for (int i = 0; infix[i]; i++) {
        char symbol = infix[i];

        if (eh_digito(symbol)) {
            int val = le_numero(infix, &i);
            pilha_push(saida, ab_no_novo(OPERANDO, val, NULL, NULL));
        } else if (symbol == '(') {
            pilha_push(pilha, (void *) symbol);
        } else if (symbol == ')') {
            for (char opr = (char) pilha_pop(pilha); opr != '('; opr = (char) pilha_pop(pilha)) {
                NoArvBin *dir = pilha_pop(saida);
                NoArvBin *esq = pilha_pop(saida);
                NoArvBin *no = ab_no_novo(OPERADOR, opr, esq, dir);
                pilha_push(saida, no);
            }
        } else {
            while (!pilha_vazia(pilha)) {
                char opr = (char) pilha_pop(pilha);
                if (opr == '(' || prioridade_operador(opr) < prioridade_operador(symbol)) {
                    pilha_push(pilha, (void *) opr);
                    break;
                } else {
                    NoArvBin *dir = pilha_pop(saida);
                    NoArvBin *esq = pilha_pop(saida);
                    NoArvBin *no = ab_no_novo(OPERADOR, opr, esq, dir);
                    pilha_push(saida, no);
                }
            }
            pilha_push(pilha, (void *) symbol);
        }

    }

    while (!pilha_vazia(pilha)) {
        NoArvBin *dir = pilha_pop(saida);
        NoArvBin *esq = pilha_pop(saida);
        NoArvBin *no = ab_no_novo(OPERADOR, (int) pilha_pop(pilha), esq, dir);
        pilha_push(saida, no);
    }

    NoArvBin *result = pilha_pop(saida);
    assert(pilha_vazia(saida));
    pilha_libera(saida, NULL);

    return result;
}

int calcule(NoArvBin *raiz) {

}

void libera_memoria(NoArvBin *raiz) {

}


int main(void) {
    NoArvBin *expr = parse_expressao("10*(2+1)*(3+5*4)");
    assert(690 == calcule(expr));

    libera_memoria(expr);
}
