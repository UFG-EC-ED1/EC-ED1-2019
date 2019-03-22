# Linguagem C

## Programa básico em C

```C
// inclui o arquivo stdio.h usando o préprocessador
#include <stdio.h>

// função main define o ponto de início do programa
int main(void) {

  // imprime uma cadeia de caracteres na saída padrão
  printf("Hello");
  printf(" World!\n");

  return 0; // 0 = sem erros
}
```


## Funções

Uma função é definida pelo **tipo de dado** que ela retorna seguida pelo **nome da função** e uma **lista de parâmetros** entre parênteses. O corpo da função é definido entre chaves, conforme o exemplo abaixo.

```C
int soma(int a, int b) {
  return a + b;
}
```

> Alguns compiladores podem não apontar um erro mesmo que uma função não tenha um valor de retorno, no entanto, o comportamento durante a execução será indefinido caso o valor do retorno da função seja utilizado. Por isso toda função não ``void``deve explicitamente indicar o valor retornado utilizando a instrução ``return``.

Um procedimento é definido como uma função com o tipo de retorno ``void`` (vazio)

```C
void imprime_valor(int valor) {
  printf("%d\n", valor);
}
```

Uma função que não recebe parâmetros deve incluir o termo ``void`` no lugar da lista de parâmetros, como no exemplo abaixo.

```C
int f(void) {
  return 10;
}
```

Se nenhum parâmetro for definido, o compilador assume que a função pode receber qualquer número de argumentos.
```C
int f() {
  return 10;
}

int main() {
  f(10);
  f(10, 20);
  return 0;
}
```

> O código acima compila normalmente, pois a função ``f`` pode receber uma quantidade variável de argumentos. Neste exemplo os parâmetros não são usados no corpo da função, e o objetivo é apenas ilustrar essa características. Na biblioteca padrão C existem várias funções que aceitam variável de argumentos como ``scanf`` e ``printf``.

## Biblioteca padrão C

```C
#include <stdio.h>
#include <math.h>

int main(void) {
  double a, b, c;

  scanf("%lf %lf %lf", &a, &b, &c);

  double delta = pow(b, 2) - 4 * a * c;

  if (delta < 0 || a == 0) {
    puts("Impossivel calcular");
    return 0;
  }

  double result1 = (-b + sqrt(delta)) / (2 * a);
  double result2 = (-b - sqrt(delta)) / (2 * a);  

  printf("R1 = %.5lf\nR2 = %.5lf\n", result1, result2);

  return 0;
}
```


## Registros

```C
struct usuario {
  char identificador[30];
  char senha[30];
  char email[30];
  char nome_completo[50];
}
```


```C

struct notas_aluno {
  float prova1;
  float prova2;
  float trabalhos;
};

struct aluno {
  int matricula;
  char nome[30];
  struct notas_aluno notas;
  /* demais campos... */
};

float calcula_media(struct notas_aluno notas) {
  return 0.35 * nota.prova1
       + 0.35 * nota.prova2
       + 0.30 * nota.trabalhos;
}

void imprime_resultado(struct aluno aluno) {
  printf("%05d %30s %.2f\n",
      aluno.matricula,
      aluno.nome,
      calcula_media(aluno.notas);
}
```

#### Outros exemplos:

```C
struct tm {
 int tm_sec;  /* seconds,  range 0 to 59          */
 int tm_min;  /* minutes, range 0 to 59           */
 int tm_hour;  /* hours, range 0 to 23             */
 int tm_mday;  /* day of the month, range 1 to 31  */
 int tm_mon;  /* month, range 0 to 11             */
 int tm_year;  /* The number of years since 1900   */
 int tm_wday;  /* day of the week, range 0 to 6    */
 int tm_yday;  /* day in the year, range 0 to 365  */
 int tm_isdst;  /* daylight saving time             */
};

time_t mktime(struct tm *timeptr)
```

## ``union``
```C
union inteiro {
  char bytes[4];
  int32_t valor;
}
```


```C
union dados_mistos {
	int inteiro;
	float racional;
	char texto[30];
};

struct dados {
  int tipo;
  union dados_mistos;
}

```
## Préprocessador
Exemplo de uso do préprocessador  para definir uma constante e uma macro.
```C
#include <stdio.h>
#include "meu_arquivo.h"

#define PI 3.14159

#define AREA_CIRCULO(x) (PI * (x) * (x))

int main(void) {
  double raio;
  scanf("%lf", &raio);
  printf("AREA = %.5lf\n", AREA_CIRCULO(raio));

}
```

Exemplo de código usando condicionais de macro para garantir portabilidade
```C
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#endif
```

## Ponteiros

#### Passagem por valor e por referência.
```C
#include <stdio.h>

// passagem por valor (variáveis na pilha)
void troca(int a, int b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int main(void) {
  int a = 10, b = 20;

  troca(a, b);
  printf("%d %d\n", a, b); // imprime 10 20

  return 0;
}
```


```C
#include <stdio.h>

// passagem por referência (endereço na pilha)
void troca(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main(void) {
  int a = 10, b = 20;

  troca(a, b);
  printf("%d %d\n", &a, &b); // imprime 20 10

  return 0;
}
```


#### Operadores de endereço e ponteiro
```C
#include <stdio.h>

int main(void) {
  int a = 10;

  printf("%d\n", a);
  printf("%p\n", &a); // &a representa o endereço de onde a variável a está armazenada

  return 0;
}
```

```C
#include <stdio.h>
int main(void) {
  int a = 1, *ap;  // Declara um inteiro e um ponteiro para inteiro

  ap = &a;

  printf("%p %p\n", ap, &a); // ap == &a
  printf("%d %d\n", *ap, a); // *ap == a

  printf("%d %d\n", *&a, a); // os operadores podem ser combinados

  return 0;
}
```
> O símbolo asterisco ``*`` é utilizado tanto na declaração de um ponteiro quanto para o "dereferenciamento" de um endereço. A operação de "deferenciamento" consiste em acessar o valor que está armazenado no endereço referenciado pelo ponteiro.

#### Ponteiros e vetores

Um vetor funciona como um ponteiro constante, que não pode ser alterado para um outro endereço.

```C
#include <stdio.h>
int main (void) {
  int vetor1[] = { 5, 4, 3, 2, 1 };
  int vetor2[] = { 1, 2, 3, 4, 5 };
  int *ptr;

  // o ponteiro é apontado para o início do vetor1, ou seja seu primeiro elemento
  // ptr = &vetor1[0];
  ptr = vetor1;
  printf("%d\n", *ptr); // imprime o valor na primeira posição do vetor1, ou seja 5

  ptr = &vetor1[1]; // ptr é atribuído à segunda posição do vetor1
  printf("%d\n", *ptr); // imprime o valor na segunda posição do vetor1, ou seja 4

  ptr = vetor2;
  printf("%d\n", *ptr); // imprime o valor na primeira posição do vetor2, ou seja 1

  return 0;
}
```

#### Cadeias de caracteres

```C
#include <stdio.h>  


int main(void) {  
    // cadeia de caracteres é representada por um  
 // vetor de caracteres terminando com o caractere nulo '\0';  char mensagem[] = "Olá mundo"; // array de tamanho 10 (9 caracteres + 1 terminador)  
 //                 012345679  
  printf("Mensagem: %s\n", mensagem); // imprime a mensagem, exemplo  

  char *ptr_mensagem = mensagem;  
    printf("Mensagem: %s\n", ptr_mensagem);  

    printf("Valor na última posição: %d\n", mensagem[10]); // imprime 0  


 // cadeias constantes também podem ser diretamente definidas como ponteiros  char *outra_mensagem = "Hello world";  
    printf("Mensagem: %s\n", outra_mensagem);  

    return 0;  

}
```


#### Aritmética de ponteiros

Um ponteiro pode ser incrementado ou decrementado.
```C
#include <stdio.h>  

int main(void) {  
  int vetor[] = { 10, 1, 5, 3, 10, 50, 20 }; // 7 elementos  
  int *vetor_ptr = vetor;  

  printf("%u\n", vetor_ptr); // endereço de vetor[0]  
  printf("%u\n", vetor_ptr + 1); // endereço de vetor[1]  
  printf("%u\n", vetor_ptr + 2); // endereço de vetor[2]  

  printf("%d == %d\n", vetor[5], *(vetor + 5));  

  vetor_ptr = &vetor[6]; // último elemento  
  vetor_ptr--; // agora vetor_ptr aponta para o 6o elemento  

  for (vetor_ptr = vetor; vetor_ptr < vetor + 7; vetor_ptr++) {  
    printf("%d ", *vetor_ptr);  
  }
  printf("\n");

  for (int i = 0; i < 7; i++) {
    printf("%d ", vetor_ptr[i]);
  }
  printf("\n");

  return 0;  
}
```


#### ``malloc`` &  ``free``
```C

// Aloca uma região de memória de size bytes
// Retorna um ponteiro para o início da posição da memória
// Retorna um ponteiro nulo (0) se não for possível alocar memória
void* malloc (size_t size);

// Libera o espaço alocado previamente
void free (void* ptr);
```


```C
#include <stdio.h>
#include <stdlib.h> // malloc e free

int main(void) {
  int n_entradas, valor;

  printf("Digite a quantidade de entradas: ");
  scanf("%d", &n_entradas);

  // aloca uma quantidade de memória suficiente para n_entradas inteiros
  int *vetor = malloc(sizeof(int) * n_entradas);

  printf("Digite os valores\n");
  for (int i = 0; i < n_entradas; i++) {
	  scanf("%d", &vetor[i]); // scanf("%d", vetor + i);
  }

  free(vetor);

  return 0;
}
```

#### ``realloc``
```C
// modifica o tamanho da memória previamente alocada apontada por ptr para size
// o novo tamanho pode ser maior ou menor
// se não consegue alocar o retorno é 0 e o ponteiro anterior continua válido
void* realloc (void* ptr, size_t size);

// aloca um bloco de memória de tamanho num * size e inicializa com 0s
void* calloc (size_t num, size_t size);
```


```C
#include <stdio.h>
#include <stdlib.h> // malloc e free

int main(void) {
  int valor;

  // aloca uma quantidade de memória suficiente para n_entradas inteiros
  int *vetor = malloc(sizeof(int) * n_entradas);

  printf("Digite os valores\n");
  for (int i = 0; i < n_entradas; i++) {
	  scanf("%d", &vetor[i]); // scanf("%d", vetor + i);
  }

  free(vetor);

  return 0;
}
```
