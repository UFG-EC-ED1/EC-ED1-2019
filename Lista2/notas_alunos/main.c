#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PESO_A1 0.35
#define PESO_A2 0.35
#define PESO_A3 0.3

struct nota_aluno {
    float a1, a2, a3;
};

float calcula_media(struct nota_aluno *nota) {
    return nota->a1 * PESO_A1
         + nota->a2 * PESO_A2
         + nota->a3 * PESO_A3;
}

#define TAM_MAX_NOME 50
struct aluno {
    unsigned int matricula;
    char nome[TAM_MAX_NOME + 1];
    struct nota_aluno nota;
};

void
le_aluno(struct aluno *aluno) {
    // É necessário \n na leitura da matrícula para garantir que a
    // leitura do texto vai se iniciar na linha seguinte
    scanf("%d\n", &aluno->matricula);

    // É necessário utilizar fgets pois scanf lê apenas uma palavra, enquanto
    // o nome do aluno pode conter várias "palavras"
    fgets(aluno->nome, TAM_MAX_NOME, stdin);
    assert(strlen(aluno->nome) > 0);
    scanf("%f %f %f", &(aluno->nota.a1),
                      &(aluno->nota.a2),
                      &(aluno->nota.a3));
}

struct aluno *
busca_aluno(int matricula, struct aluno *alunos, size_t n) {
    for (int i = 0; i < n; i++) {
        if (alunos[i].matricula == matricula)
            return alunos + i;
    }

    return NULL;
}


int main(void) {
    unsigned int qtd_alunos;
    scanf("%u", &qtd_alunos);

    struct aluno *alunos = malloc(sizeof(struct aluno) * qtd_alunos);
    for (int i = 0; i < qtd_alunos; i++) {
        le_aluno(alunos + i);
    }

    unsigned int matricula;
    while (scanf("%u", &matricula) != EOF) {
        struct aluno *aluno = busca_aluno(matricula, alunos, qtd_alunos);
        if (aluno == NULL) {
            fprintf(stderr, "ERRO: Aluno com matrícula \'%d\' não encontrado\n", matricula);
        } else {
            float media = calcula_media(&aluno->nota);
            printf("%d - %s - %.1f\n", aluno->matricula, aluno->nome, media);
        }
    }
}
