## Atividade 6

1. Construa manualmente (usando papel e caneta/lápis) uma árvore binária de busca obtida a partir da inserção dos seguintes elementos: [10, 2, 5, 14, 22, 4, 13, 3, 1, 11]


2. Considere que estamos buscando o nó onde se encontra o elemento 3, enumere quais os nós são visitados durante a busca por esse nó.

3. Implemente uma função que insira um elemento em uma árvore binária de busca. A função deve receber um ponteiro para o nó raiz da árvore e o elemento a ser inserido. A função retorna um ponteiro para o nó raiz da árvore. Uma árvore vazia pode ser representada por um ponteiro com o valor ``NULL``.

  Deve ser considerada a propriedade da árvore de busca binária: dado qualquer nó da árvore todos os nós em sua subárvore esquerda possuem valor inferior; e todos os nós em sua subárvore direita possuem valor superior (ou igual quando possível elementos repetidos).

4. Implemente uma função que busque um elemento em uma árvore binária de busca. A função deve receber um ponteiro para o nó raiz e um valor e retornar o nó contendo o elemento procurado.

5. As funções acima podem ser implementadas de forma recursiva ou iterativa. Reimplemente as funções acima usando uma estratégia diferente da usada anteriormente.



  >Nos exercícios acima considere a estrutura de nó em árvore binária dada abaixo.
  ```C
  typedef struct tree_node TreeNode;
  struct tree_node {
    int data;
    TreeNode *left, *right;
  };
  ```
