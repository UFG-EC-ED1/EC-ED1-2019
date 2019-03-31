#include <stdio.h>

int main(void) {
  int divisores[] = { 2, 3, 4, 5 };
  int totais[] = { 0, 0, 0, 0 };
  const int qtd_divisores = 4;

  int n_entradas, i;


  scanf("%d", &n_entradas);
  while (n_entradas-- > 0) {
    int valor;
    scanf("%d", &valor);

    for (i = 0; i < qtd_divisores; i++) {
      if (valor % divisores[i] == 0)
        totais[i]++;
    }
  }

  for (i = 0; i < qtd_divisores; i++)
    printf("%d Multiplo(s) de %d\n", totais[i], divisores[i]);

  return 0;
}
