#include <stdio.h>

/**
Uma solução mais eficiente pode ser obtida utilizando programação dinâmica.
No site abaixo há uma discussão das possíveis soluções
https://www.geeksforgeeks.org/longest-common-substring-dp-29/
*/


/*
  Conta a quantidade de caracteres iguais em str1 e str2 a partir das posições
  i em str1 e j em str2.
*/
int conta_caracteres_iguais(char str1[], int i,
                            char str2[], int j) {
    int count = 0;

    while (str1[i] && str2[j] && str1[i] == str2[j]) {
        count++;
        i++;
        j++;
    }

    return count;
}

int tam_maior_substr_comum(char str1[], char str2[]) {
    int i, j;
    int tam_maior_substr = 0;

    for (i = 0; str1[i]; i++) {
        for (j = 0; str2[j]; j++) {
            int tam_substr_comum = conta_caracteres_iguais(str1, i, str2, j);
            if (tam_substr_comum > tam_maior_substr)
                tam_maior_substr = tam_substr_comum;
        }
    }

    return tam_maior_substr;
}

#define TAM_MAX_ENTRADA 51

int main() {
    char str1[TAM_MAX_ENTRADA], str2[TAM_MAX_ENTRADA];

    while (1) {
        if (fgets(str1, TAM_MAX_ENTRADA, stdin) <= 0)
            break;

        if (fgets(str2, TAM_MAX_ENTRADA, stdin) <= 0)
            break;

        printf("%d\n", tam_maior_substr_comum(str1, str2));
    }


    return 0;
}
