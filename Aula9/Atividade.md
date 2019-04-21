

# Atividade 4

## Exercício 1
Nesse exercício utilizaremos uma estrutura de nós encadeados para representar uma lista. O código abaixo implementa algumas das funções para manipulação de nós encadeados que vimos na aula anterior.
> OBS<sub>1</sub>: Para simplificar a implementação vamos focalizar na compreensão e implementação dos algoritmos. Para isso vamos ignorar temporariamente o tratamento de memória não alocada e considerar que a função ``malloc()`` sempre consegue alocar a quantidade de memória requisitada.

> OBS<sub>2</sub>: O código abaixo não possui uma função ``main()`` e portanto não é diretamente executável. Como alguns alunos solicitaram, coloquei à  disposição em [lista.c](../Lista4/Exercicio1/lista.c) um arquivo contendo os protótipos das funções e alguns testes para validar a implementação das funções.

```C
#include <stdio.h>
#include <stdlib.h>

typedef struct no_int NoInt;
struct no_int {
    int item;       // valor armazenado no nó
    NoInt *proximo; // ponteiro para o nó seguinte
};

NoInt *
no_int_novo(int item, NoInt *proximo) {
    NoInt *no = malloc(sizeof(NoInt));

    no->item = item;
    no->proximo = proximo;

    return no;
}

NoInt *
no_int_adiciona_inicio(NoInt *cabeca, int item) {
    return no_int_novo(item, cabeca);
}

NoInt *
no_int_adiciona_fim(NoInt *cabeca, int item) {
    if (cabeca == NULL)
        return no_int_adiciona_inicio(cabeca, item);

    NoInt *no = cabeca;

    while (no->proximo != NULL)
        no = no->proximo;

    no->proximo = no_int_novo(item, NULL);

    return cabeca;
}

NoInt *
no_int_adiciona(NoInt *cabeca, int posicao, int item) {
    if (cabeca == NULL || posicao == 0)
        return no_int_adiciona_inicio(cabeca, item);

    NoInt *no = cabeca;

    while (no->proximo != NULL && --posicao > 0)
        no = no->proximo;

    no->proximo = no_int_novo(item, no->proximo);

    return cabeca;
}

NoInt *
no_int_remove_inicio(NoInt *cabeca) {
    if (cabeca == NULL)
        return NULL;

    NoInt *temp = cabeca;
    cabeca = cabeca->proximo;
    free(temp);

    return cabeca;
}

size_t
no_int_tamanho(NoInt *cabeca) {
    if (cabeca == NULL)
        return 0;

    return 1 + no_int_tamanho(cabeca->proximo);
}
```

a. Considerando essa estrutura acima, implemente uma função que obtenha o nó em uma determinada posição da lista. Caso a posição seja maior que o tamanho da lista a função deve retornar ``NULL``.

```C
NoInt *no_int_obtem(NoInt *cabeca, int posicao);
```

b. Implemente uma função que inverte a ordem de uma lista. A função deve receber um ponteiro para a cabeça (nó inicial) e manipular os ponteiros ``proximo`` da estrutura de dados do nó para obter uma lista invertida. A manipulação deve ser feita diretamente nos nós existentes, não é necessário alocar novos nós. A função deve retornar um ponteiro para ao último nó da lista (que passará a ser o primeiro).

```C
NoInt *no_int_inverte(NoInt *cabeca);
```

c. Implemente uma função que filtra os elementos de uma lista. A filtragem consiste em criar uma nova lista com os mesmos elementos da lista original, exceto os itens que correspondem ao valor filtrado. Por exemplo ``filtro([10, 2, 3, 10, 2, 4], 2) = [10, 3, 10, 4]``. Lembre-se que uma lista pode conter vários itens repetidos.

```C
NoInt *no_int_filtro(NoInt *cabeca, int valor_filtrado);
```

> OBS: Neste exercício estamos filtrando apenas os itens que tem exatamente o mesmo valor passado como parâmetro, mas mais adiante podemos modificar a função para filtrar baseado em critérios, como por exemplo, todos os itens pares, todos itens menores que 10, etc.

## Exercício 2

Nos exercícios anteriores utilizamos diretamente a estrutura de nós para representar e manipular uma sequencia de itens. No entanto, essa abordagem tem algumas limitações. Primeiramente, ela requere que o cliente (programa que utiliza a estrutura) tenha conhecimento sobre a representação de nós, mas também impossibilita armazenar informações adicionais como a quantidade de itens na lista.

Como vimos na última aula, podemos criar uma estrutura de dados que encapsula essas informações e as operações de manipulação de nós.

```C
typedef struct lista_int {
    NoInt *cabeca;    // ponteiro para a cabeça da lista
    size_t qtd;       // qtd de elementos na lista
} ListaInt;

ListaInt *
lista_novo(void) {
    ListaInt *lista = malloc(sizeof(ListaInt));

    lista->cabeca = NULL;
    lista->qtd = 0;

    return lista;
}

void
lista_adiciona(ListaInt *lista, int posicao, int item);

int
lista_obtem(ListaInt *lista, int posicao);

void
lista_adiciona_fim(Lista *lista, int item);

void
lista_libera(ListaInt *lista);
```

a. Implemente as funções ``lista_adiciona()`` e ``lista_obtem()``, você pode reutilizar a estrutura de dados de nós e as funções já disponíveis e implementadas no exercício anterior.

b. Como vimos no exercício anterior, para adicionar um item ao fim da lista é necessário percorrer toda a lista até encontrar o último nó. Uma melhoria que pode ser feita para facilitar a inserção no fim da lista é manter na estrutura da lista um ponteiro para o último nó. Adicione um ponteiro para o último elemento da lista e implemente a função ``lista_adiciona_fim()`` utilizando o ponteiro auxiliar. Não se esqueça de atualizar a implementação da função ``lista_adiciona()``.


c. (Bonus) Implemente uma função que libere a memória utilizada pela lista. Para isso é necessário liberar não só a estrutura alocada pela lista, mas a estrutura utilizada por cada nó.

d. (Bonus) Caso você tenha implementado a função anterior de forma iterativa, implemente a novamente utilizando recursão.

```C
void lista_int_libera(ListaInt *lista);
```

## Exercício 3

Crie uma implementação de uma lista ordenada. Em uma lista ordenada os itens são sempre mantidos em ordem. Sempre que um item é adicionado, ele é colocado diretamente em sua posição. Para esse exercício você só precisa implementar a função ``lista_adiciona()``.

> O arquivo .c com os testes será disponibilizado em breve

```C
typedef struct lista_no lista_no_t;
struct lista_no {
  int item;
  lista_no_t *proximo;
};

typedef struct {
  lista_no_t *cabeca;
  size_t tamanho;
} lista_t;

#define lista_tamanho(l) ((l)->tamanho)
#define lista_vazia(l) ((l)->tamanho == 0)
#define lista_no_inicio(l) ((l)->cabeca)

void
lista_adiciona(lista_t *lista, int item);

int
lista_obtem(lista_t *lista, int posicao) {
  assert(posicao < lista_tamanho(lista));

  lista_no_t *no = lista->cabeca;
  while (posicao-- > 0)
    no = no->proximo;

  return no->item;
}

int
lista_remove_inicio(lista_t *lista) {
  assert(lista->cabeca != NULL);

  lista_no_t *temp = lista->cabeca;
  lista->cabeca = temp->proximo;
  int result = temp->item;
  free(temp);
  return result;
}

int
lista_remove(lista_t *lista, size_t posicao) {
  if (posicao == 0)
    return lista_remove_inicio(lista);

  No *anterior = lista->cabeca;
  while (--posicao > 0)
    anterior = anterior->proximo;

  lista_no_t *temp = anterior->proximo;
  anterior->proximo = temp->proximo;
  int result = temp->item;
  free(temp);

  return result;
}

```

## Exercício 4 (Extra)

Vocês devem ter percebido que quase todas as funções de manipulação de nós encadeados é preciso verificar o caso onde a cabeça (nó inicial) é nulo, como um caso especial de lista.

Isso acontece porque para remover ou adicionar um item de uma lista encadeada é necessário sempre encontrar o nó anterior à posição onde o item será removido/adicionado. Na forma como estávamos trabalhando, o primeiro elemento era nulo quando a lista está vazia e portanto, uma tentativa de acessar o nó seguinte utilizando o ponteiro ``proximo`` geraria um erro.

Uma solução geralmente utilizada para esse problema é a criação de um nó "sentinela". Um nó vazio, que não guarda nenhum valor como dado, mas cujo ponteiro proximo aponta para a cabeça. O uso de tal nó permite generalizar os algoritmos de inserção/remoção na lista, pois mesmo no caso de a lista estar vazia existe um nó anterior ao início, que é o nó sentinela.

Reescreva a lista criada no exercício 2 utilizando um nó sentinela.


```
  Nó sentinela          nó 0             nó 1                    nó final
   ___________      ___________      ___________               ___________
  |     |     |    |     |     |    |     |     |             |     |     |
  |  ?  |    =====>|  3  |    =====>|  1  |    =====> .... ==>|  5  |NULL |
  |_____|_____|    |_____|_____|    |_____|_____|             |_____|_____|

```
