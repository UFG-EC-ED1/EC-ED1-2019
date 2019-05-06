//
// Created by gustavo on 03/05/19.
//
#include "aluno.h"
#include <stdlib.h>
#include <string.h>

aluno_t *
aluno_novo(const char *nome, float n1, float n2, float n3) {
    aluno_t *aluno = malloc(sizeof(aluno_t));
    strncpy(aluno->nome, nome, ALUNO_NOME_TAM_MAX);
    aluno->n1 = n1;
    aluno->n2 = n2;
    aluno->n3 = n3;
    return aluno;
}

double
aluno_calcula_media(aluno_t *aluno) {
    return aluno->n1 * 0.35 + aluno->n2 * 0.35 + aluno->n3 * 0.3;
}

void
aluno_imprime(aluno_t *aluno, FILE *saida) {
    fprintf(saida, "%s [%.1lf]\n", aluno->nome, aluno_calcula_media(aluno));
}

void
aluno_libera(aluno_t *aluno) {
    free(aluno);
}