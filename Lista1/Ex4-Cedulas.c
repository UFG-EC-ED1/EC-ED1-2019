#include <stdio.h>
 
int main() {
    int i, valor, notas[] = { 100, 50, 20, 10, 5, 2, 1 };

    scanf("%d", &valor);
    
    printf("%d\n", valor);
    for (i = 0; i < 7; i++) {
        int tamanho_nota = notas[i];
        int qtd_notas = valor / tamanho_nota;
        printf("%d nota(s) de R$ %d,00\n", qtd_notas, tamanho_nota);
        valor = valor % tamanho_nota;
    }

 
    return 0;
}
