//
// Created by gustavo on 05/05/19.
//

#ifndef ED1_GENERICO_ALUNO_H
#define ED1_GENERICO_ALUNO_H

#include <stdio.h>

#define ALUNO_NOME_TAM_MAX 100

typedef struct {
    char nome[ALUNO_NOME_TAM_MAX + 1];
    float n1, n2, n3;
} aluno_t;

aluno_t *
aluno_novo(const char *nome, float n1, float n2, float n3);

double
aluno_calcula_media(aluno_t *aluno);

void
aluno_imprime(aluno_t *aluno, FILE *saida);

void
aluno_libera(aluno_t *aluno);

#endif //ED1_GENERICO_ALUNO_H
