#include <stdio.h>

#define TAM_MATRIZ 12

float soma(float vetor[], size_t n) {
    int i;
    float total = 0;

    for (i = 0; i < n; i++)
        total += vetor[i];

    return total;
}

float media(float vetor[], size_t n) {
    return soma(vetor, n) / n;
}

float calcula_resultado(char acao, float vetor[], size_t n) {
    switch (acao) {
        case 'S':
            return soma(vetor, n);
        case 'M':
            return media(vetor, n);
    }

    return -1; // ERRO
}

int main(void) {
    int linha;
    char acao;
    float matriz[TAM_MATRIZ][TAM_MATRIZ];
    int i, j;

    scanf("%d %c", &linha, &acao);

    for (i = 0; i < TAM_MATRIZ; i++) {
        for (j = 0; j < TAM_MATRIZ; j++) {
            scanf("%f", &matriz[i][j]);
        }
    }

    printf("%.1f\n", calcula_resultado(acao, matriz[linha], TAM_MATRIZ));

    return 0;
}
