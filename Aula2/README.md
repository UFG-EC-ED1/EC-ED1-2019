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

#### ``malloc`` &  ``free``
```C

// Aloca uma região de memória de size bytes
void* malloc (size_t size);

// Libera o espaço alocado previamente
void free (void* ptr);
```
