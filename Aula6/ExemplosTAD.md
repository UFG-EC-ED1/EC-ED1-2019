## Exemplos de implementação de alguns Tipos Abstratos de Dados

### Ponto (implementação com acesso aos membros)
```C
/* ponto.h */
#ifndef __PONTO_H__
#define __PONTO_H__

typedef struct ponto {
	double x, y;
} Ponto;

Ponto *ponto_novo(double x, double y);

double ponto_calc_distancia(Ponto *a, Ponto *b);

void ponto_libera(Ponto *ponto);

#endif __PONTO_H__
```

```C
/* ponto.c */
#include "ponto.h"
#include <stdlib.h>
#include <assert.h>

Ponto *
ponto_novo(double x, double y) {
	Ponto *ponto = malloc(sizeof(Ponto));
	if (ponto != NULL) {
		ponto->x = x;
		ponto->y = y;
	}

	return ponto;
}

double
ponto_calc_distancia(Ponto *a, Ponto *b) {
	assert(a != NULL && b != NULL);

	double dx = a->x - b->x;
	double dy = a->y - b->y;

	return sqrt(dx * dx + dy * dy);
}

void
ponto_libera(Ponto *p) {
	assert(p != NULL);
	free(p);
}
```


### Ponto (implementação sem acesso aos membros)
```C
/* ponto.h */
#ifndef __PONTO_H__
#define __PONTO_H__

typedef struct ponto Ponto;

Ponto *ponto_novo(double x, double y);

double ponto_get_x(Ponto *ponto);
double ponto_get_y(Ponto *ponto);
void ponto_get_xy(Ponto *ponto, double *x, double *y);

double ponto_set_x(Ponto *ponto, double x);
double ponto_set_y(Ponto *ponto, double y);
double ponto_set_xy(Ponto *ponto, double x, double y);

double ponto_calc_distancia(Ponto *a, Ponto *b);

void ponto_libera(Ponto *ponto);

#endif __PONTO_H__
```

```C
/* ponto.c */
#include "ponto.h"
#include <stdlib.h>
#include <assert.h>

struct ponto {
	double x, y;
};

Ponto *ponto_novo(double x, double y) {
	Ponto *ponto = malloc(sizeof(Ponto));
	if (ponto != NULL) {
		ponto->x = x;
		ponto->y = y;
	}

	return ponto;
}
double ponto_get_x(Ponto *ponto) {
	assert(ponto != NULL);
	return ponto->x;
}

double ponto_get_y(Ponto *ponto) {
	assert(ponto != NULL);
	return ponto->y;
}

void ponto_get_xy(Ponto *ponto, double *x, double *y) {
	assert(ponto != NULL);
	if (x != NULL)
		*x = ponto->x;
	if (y != NULL)
		*y = ponto->y;
}

double ponto_set_x(Ponto *ponto, double x) {
	assert(ponto != NULL);
	ponto->x = x;
}

double ponto_set_y(Ponto *ponto, double y) {
	assert(ponto != NULL);
	ponto->y = y;
}

double ponto_set_xy(Ponto *ponto, double x, double y) {
	assert(ponto != NULL);
	ponto->x = x;
	ponto->y = y;
}

double ponto_calc_distancia(Ponto *a, Ponto *b) {
	assert(a != NULL && b != NULL);

	double dx = a->x - b->x;
	double dy = a->y - b->y;

	return sqrt(dx * dx + dy * dy);
}

void ponto_libera(Ponto *p) {
	assert(p != NULL);
	free(p);
}
```
### Ponto (usando um vetor)

```C
#ifndef __PONTO_H__
#define __PONTO_H__

typedef double Ponto;

Ponto *ponto_novo(double x, double y);

double ponto_get_x(Ponto *ponto);
double ponto_get_y(Ponto *ponto);

void ponto_libera(Ponto *ponto);

#endif

```


```C
/* ponto.c */
Ponto *ponto_novo(double x, double y) {
  Ponto *ponto = malloc(sizeof(Ponto) * 2);
  if (ponto != NULL) {
    ponto[0] = x;
    ponto[1] = y;    
  }

  return ponto;
}

double ponto_get_x(Ponto *p) {
  return p[0];
}

double ponto_get_y(Ponto *p) {
  return p[1];
}

void ponto_libera(Ponto *p) {
  free(p);
}

```



### Retângulo
```C
/* retangulo.h */

#ifndef __RETANGULO_H__
#define __RETANGULO_H__

typedef struct retangulo {
	Point *p1, *p2;
} Retangulo;

Retangulo *
retangulo_novo(Point *p1, Point *p2);

Retangulo *
retangulo_novo_coord(double x1, double y1, double x2, double y2);

double
retangulo_calc_area(Retangulo *rect);

void
retangulo_libera(Retangulo *rect);

#endif
```


### Tela

```C
/* tela.h */

typedef struct tela Tela;

void desenha_linha(Tela *tela, Ponto *p1, Ponto *p2);
void desenha_retangulo(Tela *tela, Retangulo *r);
void desenha_circulo(Tela *tela, Circulo *c);
```

### Conjunto
```C
#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <stdbool.h>

/**
  Tipo abstrato para manter um conjunto de inteiros
*/
typedef struct conjunto_ conjunto_t;

/**
  Cria um novo conjunto vazio.
  retorna NULL se não consegue alocar memória
*/
conjunto_t *conjunto_novo(void);

/**
  Cria um novo conjunto e adiciona os itens do vetor especificado pelos parâmetros vetor e qtd.
  retorna NULL se não consegue alocar memória.
*/
conjunto_t *conjunto_novo_lendo_vetor(int *vetor, size_t qtd);


/**
  Verifica se um conjunto já contem um elemento.
*/
bool conjunto_contem(conjunto_t *conjunto, int elemento);

/**
  Adiciona um elemento ao conjunto.
  retorna false se não for possível adicionar  
*/
bool conjunto_adiciona(conjunto_t *conjunto, int elemento);

/**
  Retorna a quantidade de elementos em um conjunto
*/
size_t conjunto_qtd_itens(conjunto_t *conjunto);

/**
  Retorna um novo conjunto cujos elementos são a interseccao entre os conjuntos a e b.
  Retorna NULL se não consegue alocar memória para o novo conjunto
*/
conjunto_t *conjunto_intersecao(conjunto_t *a, conjunto_t *b);

/**
  Retorna um novo conjunto cujos elementos são a união entre os conjuntos a e b.
  Retorna NULL se não consegue alocar memória para o novo conjunto
*/
conjunto_t *conjunto_uniao(conjunto_t *a, conjunto_t *b);

/**
  Compara se dois conjuntos são iguais, i.e. contém os mesmos elementos
*/
bool conjunto_iguais(conjunto_t *a, conjunto_t *b);

/**
  Libera a memória usada no armazenamento do conjunto.
*/
void conjunto_libera(conjunto_t *conjunto);

#endif
```
