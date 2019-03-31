#include <stdio.h>

#define TAM_MATRIZ 12

int main(void) {
    char acao;
    double matriz[TAM_MATRIZ][TAM_MATRIZ];
    int col, linha;

    double soma = 0;
    int n = 0;

    scanf("%c", &acao);

    // Lê uma linha à linha
    for (linha = 0; linha < TAM_MATRIZ; linha++) {
        for (col = 0; col < TAM_MATRIZ; col++) {
            scanf("%lf", &matriz[linha][col]);
        }
    }

    // Percorre cada linha da parte superior [0 - 4]
    for (linha = 1; linha <= 5; linha++) {
        for (col = linha; col < TAM_MATRIZ - linha; col++) {
            soma += matriz[linha - 1][col];
            n++;
        }
    }


    printf("%.1lf\n", acao == 'S' ? soma : soma / n);


    return 0;
}
