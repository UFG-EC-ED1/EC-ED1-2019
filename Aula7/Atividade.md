# Atividade 3

Para essa atividade vamos desenvolver uma estrutura de dados que implementa o tipo abstrato de dados **conjunto**. A principal característica de um conjunto é manter um conjunto de elementos não repetidos e não ordenados.


Existem diversas formas de se implementar um conjunto, usando diferentes estruturas de dados, cada uma com vantagens e desvantagens. Algumas soluções podem ser eficientes para verificar se um item pertence à um conjunto, outras podem ser otimizadas para reduzir o custo de operações de modificação, outros para operações de união/intersecção etc.

Uma forma simples de implementar um conjunto é manter um vetor de elementos ignorando a ordem dos elementos e tratando de evitar que elementos repetidos sejam adicionados. Apesar de essa não ser a solução mais eficiente, neste momento vamos nos concentrar em obter uma implementação funcional, que atenda às especificações do tipo de dados conjunto, sem nos preocuparmos com a questão de desempenho. Mais a frente veremos que existem outras estruturas de dados como árvores, tries e tabelas de espalhamento (*hash tables*) que podem ser utilizadas para implementar conjuntos de forma mais eficiente.

Nessa atividade vamos implementar um conjunto de números inteiros, mas a implementação poderá ser facilmente generalizada para outros tipos futuramente.

## Interface

A interface (conjunto de operações) que iremos implementar nessa atividade está definida no arquivo [conjunto.h](./ed1_conjunto/conjunto.h).

Pela descrição de interface acima podemos identificar 11 operações que podem ser classificadas da seguinte forma:

- Criação

```C
conjunto_t *
conjunto_novo(void);

conjunto_t *
conjunto_novo_lendo_vetor(int *vetor, size_t qtd);
```

- Produção

```C
conjunto_t *
conjunto_intersecao(conjunto_t *a, conjunto_t *b);

conjunto_t *
conjunto_uniao(conjunto_t *a, conjunto_t *b);
```

- Leitura

```C
bool
conjunto_contem(conjunto_t *conjunto, int elemento);

size_t
conjunto_qtd_itens(conjunto_t *conjunto);

bool
conjunto_iguais(conjunto_t *a, conjunto_t *b);

const int *
conjunto_vetor(conjunto_t *conjunto);
```

- Modificação

```C
bool
conjunto_adiciona(conjunto_t *conjunto, int elemento);

bool
conjunto_remove(conjunto_t *conjunto, int elemento);
```

>Além dessas, uma outra operação é necessária devido à natureza da linguagem C que requere um gerenciamento "manual" da alocação de memória. A operação ``conjunto_libera(conjunto_t *)`` tem essa função. Essa operação deve liberar a memória alocada para o vetor que armazena os valores do conjunto e da própria estrutura que mantém informações do conjunto.

Apesar de a interface conter várias operações, a maioria delas pode ser implementada em função de poucas operações básicas como adicionar, remover e verificar se um elemento está presente em um conjunto.

Por exemplo, a operação ``conjunto_novo_lendo_vetor()`` pode ser implementada utilizando a operação ``conjunto_novo()`` para criar um novo conjunto vazio e chamando sucessivamente a operação ``conjunto_adiciona()`` para adicionar cada item do vetor ao conjunto.

A operação de união (``conjunto_uniao()``) pode ser implementada criando um novo conjunto (``conjunto_novo()``) e adicionando (``conjunto_adiciona()``) a esse novo conjunto todos os elementos dos conjuntos recebidos como parâmetros.

Por isso, o foco principal deve se dar na implementação dessas operações básicas: ``conjunto_adiciona()``, ``conjunto_remove()``, ``conjunto_contem()`` e ``conjunto_novo()``.


## Organização da implementação

Para essa atividade vamos organizar o código em 3 arquivos: o cabeçalho descrevendo o tipo abstrato [conjunto.h](./ed1_conjunto/conjunto.h), a implementação [conjunto.c](./ed1_conjunto/conjunto.c) e um arquivo de teste que verifica se a implementação está correta [conjunto_test.c](./ed1_conjunto/conjunto_test.c). Os arquivos de cabeçalho e teste já estão fornecidos e **não devem ser alterados**. A sua solução estará correta se o programa de teste executar sem nenhum erro.

Se você está utilizando uma IDE como Code::Blocks basta criar um projeto novo e adicionar esses arquivos ao projeto. Caso esteja utilizando a linha de comandos há um arquivo [Makefile](./ed1_conjunto/Makefile) que permite compilar e executar os testes digitando ``make test``.

Já há um arquivo [conjunto.c](./ed1_conjunto/conjunto.c) onde estão definidas as funções, algumas com implementações vazias.


>**OBSERVAÇÃO**: É importante notar que nesta atividade não estamos implementando um programa que receberá entrada de dados, mas uma biblioteca que contém uma implementação do tipo abstrato conjunto. Essa biblioteca poderá ser utilizada futuramente na criação de um programa.

> Para verificar se o funcionamento da estrutura está correto durante a sua implementação utilizamos o programa de teste contido no arquivo [conjunto_test.c](./ed1_conjunto/conjunto_test.c). Não é necessário criar um outro programa contendo a função ``main()`` para receber entradas.

> Caso sinta que os testes ali presentes não são suficientes é aceitável que sejam adicionados novos testes, sem que os demais já existentes sejam suprimidos. Procurem o professor caso tenham dificuldades em como fazê-lo.


## Algoritmos

A ideia geral da solução é manter um vetor (uma região contígua de memória) onde são mantidos os elementos adicionados ao conjunto.

Antes de adicionar um novo elemento ao vetor é preciso percorrer o vetor e verificar se o elemento já está presente.

Para remover um elemento também é necessário varrer o vetor, verificar se o elemento já está presente e removê-lo.


Fique livre para criar outras funções auxiliares para dividir a complexidade da função em diferentes partes.


## Possíveis dificuldades


### Alocação dinâmica de memória

O nosso conjunto pode ser utilizado para manter uma quantidade indeterminada de elementos, de acordo com a capacidade de memória disponível no sistema. Para isso é necessário gerenciar a alocação e realocação de memória de acordo com o número de elementos no conjunto.

Antes de adicionar um novo elemento ao vetor é preciso verificar se o espaço já alocado é suficiente para armazenar o novo elemento. Caso positivo, bastará incluir o elemento em uma posição do vetor e atualizar a quantidade de elementos. Caso contrário é preciso solicitar mais memória.

Assim sendo, será necessário definir em algum momento uma certa quantidade inicial de memória para armazenar o vetor de dados, e como e com o assunto  quantidade será aumentada. Uma solução simples é definir um tamanho arbitrário para uma alocação inicial (escolha um valor pequeno, como 50, para que o programa de teste consiga verificar essa-  parte do algoritmo) e dobrar a quantidade de memória quando for necessário aument- ar Atividade 03 tamanho alocado.

Essa verificação deve ser feita ça operação ``conjunto_adiciona()``, antes de adicionar 3 elemento ao vetor. Se não houver mais espaço suficiente. para o novo item, deve ser alocado/realocado um novo vetor.

Da mesma forma, após remover um elemento, podemos verificar se há muito espaço alocado de forma desnecessária e liberar memória. Podemos de forma similar verificar se a quantidade de elementos é menor que a metade do tamanho do vetor alocado e diminuir o espaço alocado.

## Envio

Enviar em um arquivo compactado com o seu nome (por exemplo ``Joãozinho da Silva Junior.zip``) e com o assunto [ED1 Eng Comp] - Prática - Atividade 03 - Seu Nome Completo

- Matrícula
Ex: [ED1 Eng Comp] - Prática - Atividade 03 - Joãozinho da Silva Junior - 200012345
- Turma A: Enviar para julianafelix@inf.ufg.br
- Turma B: Enviar para gustavomota@inf.ufg.br

**OBSERVAÇÃO**: Por favor não esqueça de enviar o arquivo no formato ``.zip`` e com o seu nome, fica difícil de identificar quando há vários arquivos com um nome genérico como ``Aula7.zip``.


## Recursos

Em [definição de módulos em C](./ModulosEmC.md) você pode encontrar algumas informações que ajudarão a entender como organizar o seu programa em módulos na linguagem C.
Os exemplos utilizados nas aulas anteriores ([Aula 4](../Aula4/AlocacaoDinamica.md), [Aula5](../Aula5/ModulosEmC.md), [Aula 6](../Aula6/ExemplosTAD.md)) também pode ser útil.

Para a atividade é possível utilizar as funções já disponíveis na biblioteca padrão da linguagem C. A referência para as funções pode ser encontrada em http://www.cplusplus.com/reference/
