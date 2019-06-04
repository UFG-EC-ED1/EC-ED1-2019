## Atividade 7

*Percursos em árvores*

1. Para visualizar uma árvore é necessário construir uma representação visual ou textual da mesma. Uma forma de representar uma árvore de forma textual é como uma expressão de parênteses aninhados. Por exemplo, a árvore abaixo pode ser representada pela seguinte expressão: `(1(2(4)(5(7)(8)))(3(6(9)))))`

  <img src="./arvore_ex.png" width="300px"/>


  Construa uma função que receba o nó raiz de uma árvore binária e retorne uma cadeia de caracteres com uma representação em parênteses aninhados. Considere que a árvore contém como chave apenas números inteiros.
[ex1.c](./ed1_tree/ex1.c)

2. Dada uma árvore binária, verifique se a árvore é de busca. Uma árvore binária é de busca quando para cada nó, todos os elementos na subárvore esquerda possuem chave com valor menor que a chave do nó; e todos os elementos na subárvores à direita possuem chave com valor maior.


[ex2.c](./ed1_tree/ex2.c)


3. Dada uma árvore representando uma expressão binária, calcule o valor da expressão.
[ex3.c](./ed1_tree/ex3.c)
