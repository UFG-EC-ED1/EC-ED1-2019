## Árvores

### Árvores binárias e percursos

Considerando a estrutura de nós em uma árvore binária definida abaixo (não necessariamente uma árvore de busca),
escreva o código de uma função que efetue as seguintes operações:

```C
typedef struct no_arvore NoArvore;
struct no_arvore {
  int chave;
  NoArvore *esq, *dir;
};
```

Calcule a altura de uma árvore
```C
int altura(NoArvore *raiz) {

}
```

Receba um ponteiro para o nó raiz de uma árvore e retorne o número de nó folhas.
```C
int folhas(NoArvore *raiz) {

}
```

Receba o ponteiro para o nó raiz de uma árvore e retorne a chave com maior valor.
```C
int maximo(NoArvore *raiz) {

}
```

Receba o ponteiro para o nó raiz de uma árvore e retorne um ponteiro para o nó contendo uma chave especificada (ou NULL se a chave não estiver presente na árvore).
```C
NoArvore *encontra(NoArvore *raiz, int chave) {

}
```

### Árvores binárias de busca

Considere uma **árvore binária de busca** criada a partir da inserção dos seguintes itens, na seguinte ordem:

[2, 5, 1, 9, 4, 3, 8, 6, 10, 7]

a. Construa e desenhe a árvore de busca obtida.

b. Quais as propriedades da árvore? É balanceada, completa, cheia, etc...? Qual sua altura, largura, número de folhas, etc.

c. Simule os quatro tipos de percursos na árvore (pré-ordem, pós-ordem, em-ordem e por nível)
e escreva os itens visitados, na ordem em que serão visitados, por cada percurso.

d. Qual a árvore obtida a partir da inserção de um novo item (20 por exemplo)

e. Qual a árvore obtida a partir da remoção de um novo item (4 por exemplo)


### Árvores binárias de busca

Construa uma árvore binária de busca de altura mínima, contendo as seguintes chaves 1, 2, 3, 4, 5, 6, 7.

###  Árvores binárias de busca

O código abaixo deveria verificar se uma árvore binária é uma árvore de busca, no
entanto há algum erro na implementação que

```C
bool eh_arvore_de_busca(NoArvore *raiz, int min, int max) {
  if (raiz == NULL) {
    return true;
  } else if (raiz->chave < min || raiz->chave > max) {
    return false;
  } else {
    return eh_arvore_de_busca(raiz->esq, min, raiz->chave) && eh_arvore_de_busca(raiz->dir, raiz->chave, max);
  }
}
```


### Árvores genéricas e percursos

Considere a seguinte árvore genérica, quais nós serão percorridos para encontrar o nó (X) utilizando uma busca em largura a partir do nó raiz.


## Grafos

### Representação de grafos

Dado o grafo abaixo, construa sua representação como matriz de adjacência e lista de adjacência


### Busca em grafos

1. Dado o grafo abaixo, escreva uma lista da ordem em que os vértices serão visitados em uma busca por profundidade a partir do nó X. Considere que os nós vizinhos são sempre percorridos em ordem crescente.

2. Dado o grafo abaixo, escreva uma lista da ordem em que os vértices serão visitados em uma busca por profundidade a partir do nó X. Considere que os nós vizinhos são sempre percorridos em ordem crescente.

3. Simular e encontrar um problema em um algoritmo de busca em grafos. Será fornecido um algoritmo de busca com algum problema. Você deverá simular a execução do algoritmo e comparar com a saída esperada (item 1).

### Outros

Explicar as aplicações de busca em largura/profundidade para resolução de problemas em grafos
