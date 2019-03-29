
## Atividade


### Exercício 1

A biblioteca padrão da linguagem C possui muito poucas funções para manipulação de cadeias de caracteres. Uma das funções muito comumente utilizadas em manipulação de strings é a função ``trim``, que remove espaços e tabulações no início e fim de uma cadeia de caracteres. Essa função é geralmente utilizada para "corrigir" eventuais erros na entrada de dados de usuário.

Assim sendo, a aplicação da função na cadeia de caracteres "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Estruturas de Dados 1&nbsp;&nbsp;&nbsp;&nbsp;" retornaria uma cadeia de caracteres "Estruturas de Dados 1"

Escreva uma função ``strtrim`` que recebe um ponteiro para uma cadeia de caracteres destino e um ponteiro para uma cadeia de caracteres de origem e escreva no destino a mesma cadeia sem espaços no início e fim da cadeia.

Em seguida, escreva um programa que leia uma sequencia de linhas de texto da entrada padrão e imprima o resultado da aplicação da função ``strtrim`` em cada linha.

```C

// copia origem para destino eliminando caracteres em branco e tabulação do início/fim da string
void strtrim(char *destino, char *origem);

// Exemplo de como a função pode ser utilizada
int main(void) {
  char *entrada = "      Estruturas de Dados 1   ";
  char saida[30];

  strtrim(saida, entrada);

  printf("%s\n", saida);

  return 0;
}
```
> Você pode utilizar aritmética de ponteiros para navegar entre os caracteres de uma cadeia de caracteres


### Exercício 2

Crie um programa para ajudar o professor à calcular a média dos alunos. O programa deve processar uma lista de dados de alunos: matrícula, nome e suas respectivas notas em cada uma das 3 avaliações.

Em seguida, o programa deve permitir calcular a média final e mostrar o resultado final para uma lista de alunos selecionados.

A média final é calculada com a seguinte fórmula: **0.35 \* a<sub>1</sub> + 0.35 \* a<sub>2</sub> + 0.30 \* a<sub>3</sub>**


**Entrada**

A primeira linha de entrada contém um inteiro positivo **N** (1 < N < 50) indicando o número de registros de alunos a serem lidos. A primeira linha é seguida por uma sequencia de registros contendo os seguintes dados de cada aluno: **matrícula**, **nome**, e uma linha com registros das notas de três avaliações: a<sub>1</sub>, a<sub>2</sub>, a<sub>3</sub>

Ao fim dos registros há uma sequência de números de matrículas dos alunos para os quais devem ser calculadas a média.

**Saída**

Para cada matrícula fornecida após os registros dos alunos, deve ser impressa uma linha contendo matrícula, nome e média final do aluno.

**Exemplo**

Entrada
```
2
20180201
Fulano da Silva
6.0 8.0 7.0
20180202
Joaquim dos Santos
6.0 4.0 2.0
20180202
20180201
```

Saída
```
2018201 - Fulano da Silva - 7.0
2018202 - Joaquim dos Santos - 4.1
```
> Dica: defina um tipo de registro para armazenar os dados dos alunos.


### Exercício 3

Implemente uma função ``strreverse`` que inverte a ordem dos caracteres em uma cadeia.

```C
void strreverse(char *destino, char *origem);


int main(void) {
  char *texto = "Ola mundo";
  char invertido[20];

  strreverse(invertido, texto);

  printf("%s\n", invertido); // Deve imprimir "odnum alO";

  return 0;
}

```


### Exercício 4
As funções ``strtrim`` e ``strreverse`` implementadas nos exercícios anteriores recebem como parâmetros dois ponteiros/vetores. Um para uma cadeia de caracteres contendo o texto original e outra para uma cadeia de caracteres não inicializada, mas que já foi alocada na memória préviamente.

Reescreva as funções de forma que a memória para armazenar o resultado seja alocada dinâmicamente.

As funções deverão ter o seguinte protótipo.

```C

char *strtrim_aloca(char *origem);
char *strreverse_aloca(char *origem);

// Exemplo de uso da função
int main(void) {
  char *trimmed = strtrim_aloca("    Estruturas de dados 1     ");
  char *reversed = strreverse_aloca("Ola mundo");

  printf("%s\n", trimmed);
  printf("%s\n", reversed);

  // Não esqueça de liberar a memória pois os "vetores" foram alocados dinâmicamente
  free(trimmed);
  free(reverse);

  return 0;
}

```
