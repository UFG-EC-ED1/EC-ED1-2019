
#### Regiões de memória
```C
int entrada[100];
static double media;

int max_tamanho =  99;

int main(void)  {
	int i, n;
	int soma;
	if (n > max_tamanho)
		n = max_tamanho;
	for (i =  0; i < n; i++) {
		scanf("%d", &entrada[i]);
		soma += entrada[i];
	}
	media = soma / n;
	/* ... */
	return  0;
}
```

#### Exemplos de utilização da pilha de execução

```C
int soma(int x, int y) {
	return x + y;
}

int main(void) {
	int a = 2, b = 3;
	int resultado;

	resultado = soma(a, b);

    return 0;
}
```

```C
int fat(int n) {
    if (n <= 1)
	    return 1;

	return n * fat(n - 1);
}

int main(void) {
	int x = 4;
	int fatorial = fat(x);

	printf("%d\n", fatorial);

    return 0;
}
```


```C
void troca(int *ap, int *bp) {
	int tmp *ap;
	*ap = *bp;
	*bp = tmp;
}

int main(void) {
	int a = 2, b = 3;
	troca(&a, &b);
	printf("%d %d\n", a, b);
    return 0;
}
```



#### ``malloc`` & ``free``

```C
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n_entradas;

  printf("Digite a quantidade de entradas: ");
  scanf("%d", &n_entradas);

  // aloca uma quantidade de memória suficiente para n_entradas inteiros
  int *vetor = malloc(sizeof(int) * n_entradas);

  printf("Digite os valores\n");
  for (int i = 0; i < n_entradas; i++) {
	  scanf("%d", &vetor[i]);
  }

  free(vetor);

  return 0;
}
```


Exemplo de código com erro, tenta criar uma cópia de um vetor na pilha:
```C
#include <stdio.h>  
#include <stdlib.h>  

int *copia_vetor(int vetor[], int tamanho) {  
    int i;  
    int novo_vetor[tamanho];  

    for (i = 0; i < tamanho; i++)  
        novo_vetor[i] = vetor[i];  

    return novo_vetor; // ERRO: retorna um endereço na pilha
}  

int main(void) {  
    int n_entradas;  

    printf("Digite a quantidade de entradas: ");  
    scanf("%d", &n_entradas);  

    int vetor[n_entradas];  

    printf("Digite os valores\n");  
    for (int i = 0; i < n_entradas; i++) {  
        scanf("%d", &vetor[i]); // scanf("%d", vetor + i);  
    }  

    int *novo = copia_vetor(vetor, n_entradas);  

    return 0;  
}
```

Exemplo de código para criar a cópia de um vetor.
```C
#include <stdio.h>
#include <stdlib.h>

int *copia_vetor(int vetor[], int tamanho) {
    int i;
    int *novo_vetor = malloc(sizeof(int) * tamanho);
    if (novo_vetor == NULL)
        return NULL;

    for (i = 0; i < tamanho; i++)
        novo_vetor[i] = vetor[i];

    return novo_vetor;
}

int main(void) {
    int n_entradas;

    printf("Digite a quantidade de entradas: ");
    scanf("%d", &n_entradas);

    int vetor[n_entradas];

    printf("Digite os valores\n");
    for (int i = 0; i < n_entradas; i++) {
        scanf("%d", &vetor[i]); // scanf("%d", vetor + i);
    }

    int *novo = copia_vetor(vetor, n_entradas);
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return -1;
    }

    for (int i = 0; i < n_entradas; i++) {
        printf("%d\n", novo[i]); // scanf("%d", vetor + i);
    }

    free(novo);

    return 0;
}
```



#### ``realloc``

```C
#include <stdio.h>
#include <stdlib.h> // malloc e free

int main(void) {
  int tamanho_alocado = 10;
  int *vetor = malloc(sizeof(int) * tamanho_alocado);
  int qtd_elementos = 0;

  while(fscanf(stdin, "%d", &vetor[qtd_elementos]) == 1) {
	  qtd_elementos++;
	  if (qtd_elementos == tamanho_alocado) {
		  int novo_tamanho = tamanho_alocado * 2;
		  int *novo_vetor = realloc(vetor, sizeof(int) * novo_tamanho);
		  if (vetor == NULL) {
			  fprintf(stderr, "Não foi possível alocar memória para armzenar mais itens\n");
			  return -1;
		  }
		  tamanho_alocado = novo_tamanho;
		  vetor = novo_vetor;
	  }
  }

  /* Utiliza o vetor */

  free(vetor);

  return 0;
}
```


```C
#include <stdio.h>
#include <stdlib.h> // malloc e free

int main(void) {
  int n_entradas;

  printf("Digite a quantidade de entradas: ");
  scanf("%d", &n_entradas);

  // aloca uma quantidade de memória suficiente para n_entradas inteiros
  int *vetor = malloc(sizeof(int) * n_entradas);
  if (!vetor) {
	  fprintf(stderr, "Erro ao alocar memória.\n");
	  return -1;
  }

  printf("Digite os valores\n");
  for (int i = 0; i < n_entradas; i++) {
	  scanf("%d", &vetor[i]); // scanf("%d", vetor + i);
  }

  free(vetor);

  return 0;
}
```


#### Exemplos de tipos de alocação

```C

char entrada[100]; // alocação estática não inicializada

static double media;

int max_tamanho = 99; // alocação estática inicializada

void troca(int *ap, int *bp);

void ordena(int *vetor, int n) { // alocação automática
	int i, j;  // alocação automática

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (vetor[j] < vetor[i])
				troca(vetor + j, vetor + i);
		}
	}
}

int main(void) {
	int i, n; // alocação automática
	int *vetor;

	scanf("%d", &n);
	vetor = malloc(n * sizeof(int)); // alocação dinâmica
	for (i = 0; i < n; i++)
		scanf("%d", vetor + i);

	ordena(vetor, n);

	for (i = 0; i < n; i++)
		printf("%d\n", vetor[i]);

	free(vetor);

    return 0;
}
```



#### Exemplos usando aritmética de ponteiros

```C

int main(void) {
	int v[] = { 10, 20, 30, 40 };
	int *v_ptr = v;

	// endereço do primeiro elemento
	printf("%d\n", v_ptr == &v[0] == v);

	// endereço do terceiro elemento
	printf("%d\n", (v_ptr + 2) == &v[2]);

	// valor do terceiro elemento: 30
    printf("%d\n", *(v_ptr + 2) == v[2]);

	for (int i = 0; i < 4; i++)
		printf("%d\n", *(v_ptr + i));

	return 0;
}
```
