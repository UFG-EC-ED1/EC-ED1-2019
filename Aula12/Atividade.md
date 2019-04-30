# Atividade 5

Um dos usos práticos de pilha é na manipulação de expressões, essas podem ser expressões matemáticas ou de código. A transformação entre diversas formas de representação tem como objetivo facilitar a avaliação ou manipulação dessas expressões.

Nesta atividade, construiremos um programa que avalia uma expressão matemática e retorna o seu resultado. A estrutura de dados pilha pode ser utilizada para auxiliar na transformação de expressões matemáticas e na avaliação dessas.

Antes de entrar nos detalhes da avaliação de expressões matemáticas vamos discutir sobre as possíveis formas de se representar uma expressão. A forma mais comumente utilizada de representação de expressões é a **infixa**, que é assim denominada pois os operadores são colocados entre os operandos.
```
A
A+2
(A+B)*(2-C)
```

As mesma expressões acima podem ser representadas na forma **prefixa**. Neste caso o operador precede os operandos:
```
A
+A2
*+AB-2C
```

De forma semelhante, as expressões acima podem ser representadas utilizando a forma **posfixa**:
```
A
A2+
AB+2C-*
```

As formas prefixa/posfixa possuem uma vantagem para avaliação das expressões pois dispensam a necessidade de parenteses para indicar precedência das operações. A precedência é indicada pela posição do operador e operandos. Isso possibilita a criação de algoritmos eficientes para avaliar uma expressão representada nessas formas.

Para transformar uma expressão a partir da forma infixa é preciso observar a ordem de prioridade entre diferentes operadores. Nesta atividade, iremos transformar uma expressão na forma infixa para a forma posfixa. Trabalharemos somente com os operadores de adição (+), subtração (-), multiplicação (\*), divisão (/) e parênteses. Os operadores de multiplicação e divisão têm precedência sobre os de adição e subtração, e os parênteses permitem redefinir a predcedência.

Uma propriedade importante de se notar é que a ordem dos operandos não se altera entre as expressões na forma infixa e posfixa. No entanto, a ordem dos operadores é modificada definida pela precedência.

```
Forma infixa : (A+B)*(2-C)

Forma posfixa: AB+2C-*
```

Antes de passarmos ao algoritmo de transformação, podemos discutir a ideia geral do mesmo. A estrategia utilizada é de se apropriar do fato que os operandos já estão em ordem e tentar encontrar a posição dos operadores.

Assim sendo, o algoritmo escaneia a entrada, e adiciona os operandos diretamente à expressão posfixada. Quando um operador é lido da entrada, ele é adicionado à uma pilha. Após ler os operandos, o operador é removido da pilha e adicionado à expressão posfixada.

Por exemplo, para a expressão ``A+B``, o algoritmo lê ``A`` e adiciona diretamente à saída, lê ``+`` e adiciona à uma pilha, lê ``B``e adiciona à saída, e por fim remove ``+`` da pilha e adiciona à saída.

Para expressões mais complexas o algoritmo deve verificar a prioridade entre operadores para identificar a posição correta do operador na forma posfixa. Neste caso, antes de empilhar um novo operador o algoritmo verifica se os operadores já empilhados tem prioridade maior. Operadores com prioridade maior são desempilhados sucessivamente e adicionados à saída.


O pseudocódigo abaixo descreve o algoritmo para converter da forma infixa para posfixa.
```C

infixa_para_posfixa(infixa) {
  pilha = pilha_nova()
  posfixa = ""

  while (simbolo = le_simbolo(infixa)) {
    if (eh_operando(simbolo)) {
      concatena(posfixa, simbolo)
    } else if (simbolo == '(') {
      empilha(pilha, simbolo)
    } else if (simbolo == ')') {
      // desempilha todos operadores e adiciona à saída até encontrar '('
      while ((opr = desempilha(pilha)) != '(')
        concatena(posfixa, opr)    
    } else { // símbolo é um operador
      // desempilha todos operadores e adiciona à saída até encontrar um operador
      // de prioridade menor ou parênteses
      while (!vazia(pilha)) {
        opr = topo(pilha)
        if (opr != '(' && prioridade(opr) > prioridade(simbolo)) {
          concatena(posfixa, desempilha(opr))
        } else {
          break
        }
      }
      empilha(simbolo)
    }
  }

  while (!vazia(pilha))
    concatena(posfixa, desempilha(pilha))
}
```


Exemplo de execução do algoritmo em uma expressão.
```
(A+B)*(2-C)
```
| Entrada | Pilha | Saída |
|:-------:|-------|------|
| (       | (     | |
| A       | (     | A
| +       | (+    | A
| B       | (+    | AB
| )       |       | AB+
| \*      | \*    | AB+
| (       | \*(   | AB+
| 2       | \*(   | AB+2
| -       | \*(-  | AB+2
| C       | \*(-  | AB+2C
| )       | \*    | AB+2C-
| FIM     |       | AB+2C-*



## Exercício 1

Implemente uma função em C que receba uma cadeia de caracteres com uma expressão na forma infixa e retorne uma nova cadeia de caracteres na forma posfixa. A função deve ter o seguinte protótipo.
```C
char *infixa_para_posfixa(const char *infixa);
```

> Para simplificar o tratamento das expressões vamos considerar que tanto os operadores quanto os dígitos são representados por apenas um caracter. Assim sendo os operandos permitidos são apenas variáveis de uma letra ou números de um dígito.


> Você pode utilizar a implementação de pilha apresentada na [Aula 11](../Aula11/Exemplos/ed1_pilha/), basta incluir os arquivos ``pilha_encadeada.h`` e ``pilha_encadeada.c`` no seu projeto. Alternativamente você pode manipular uma pilha diretamente em um vetor, usando um vetor de tamanho fixo e uma variável para representar o topo.



## Exercício 2

Uma vez obtida uma expressão em sua forma posfixa, também podemos utilizar uma pilha para avaliar o seu resultado. Como estamos trabalhando apenas com operadores binários, cada operador é precedido de duas subexpressões precedentes. Vamos considerar a expressão abaixo:

```
(2+5)*((6+2)/4-1)
```
Que na forma pos fixa é representada da seguinte forma
```
25+62+4/1-*
```

A idéia geral do algoritmo para avaliar uma expressão pósfixa é de escanear a expressão de entrada e sucessivamente empilhando os operandos encontrados. Quando um operador é encontrado, os dois operandos no topo da pilha são removidos e o operador é aplicado. Dessa forma, uma subexpressão é substituída pelo seu resultado, que é empilhado e será futuramente utilizado como operando em outra operação.


```C
avalia_expressao_posfixa(posfixa) {
  pilha = pilha_nova()

  while (simbolo = le_simbolo(posfixa)) {
    if (eh_operando(simbolo)) {
      empilha(pilha, simbolo)
    } else { // eh operador
      operando1 = desempilha(pilha)
      operando2 = desempilha(pilha)
      resultado = calcula(simbolo, operando1, operando2)
      empilha(pilha, resultado)
    }
  }
}
```


| Entrada | Pilha |
|:-------:|-------|
| 2 | 2
| 5 | 2 5
| + | 7
| 6 | 7 6
| 2 | 7 6 2
| + | 7 8
| 4 | 7 8 4
| / | 7 2
| 1 | 7 2 1
| - | 7 1
| * | 7


Considerando os dados acima, implemente uma função que avalia uma expressão contendo apenas números inteiros e operadores.

```C
int avalia(const char *expr);
```

> Considere que os números inteiros possuem apenas um dígito.
