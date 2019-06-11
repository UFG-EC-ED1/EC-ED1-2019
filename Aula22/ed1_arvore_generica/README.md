# Atividade 8


Nesta atividade, utilizaremos um pequeno exemplo inspirado em aplicações de gestão de contas e despesas para praticar
a manipulação de árvores genéricas para processamento de dados organizados de forma de forma hierárquica.

Em ferramentas de gestão de contas e despesas é comum que estas contas estejam organizadas em uma hierarquia. Por exemplo,
na aplicação [Gnucash](https://www.gnucash.org/) as contas (Despesas, Receitas, Ativos) são apresentadas em uma árvore
que podem ser subdividas de acordo com o desejo do usuário.

<img width="50%" src="https://www.gnucash.org/docs/v3/C/gnucash-help/figures/Main-window-callouts.png"/>

Nesta atividade tentaremos carregar informações de contas obtidas de um banco de dados e carregá-las em uma árvore para
apresentá-las ao usuário e realizar outras operações.

Os dados estão disponíveis no arquivo `contas.txt`. Este é uma arquivo CSV separado por ponto e vírgula, contendo quatro campos:
O nome da conta, o identificador da conta, o identificador do pai e o saldo da conta. Por exemplo, no trecho abaixo do arquivo
podemos ver que a conta `Despesas` possui identificador `16a2995a39b04599a996e6e2fd355f71` e sua conta pai é a conta cujo identificador
é `a7cb799944684d5faaf36793f7096f73` (conta raiz, `Root Account`), o saldo da conta (`-13.82`) encontra-se no último campo.

> OBS: Os saldos foram gerados aleatóriamente apenas para utilização no exemplo.

```
Root Account;a7cb799944684d5faaf36793f7096f73;;-0.54
Despesas;16a2995a39b04599a996e6e2fd355f71;a7cb799944684d5faaf36793f7096f73;-13.82
Receitas;32ee19d9ad5c4e08bba4dc66cf4136f5;a7cb799944684d5faaf36793f7096f73;-32.8
Passivo;bd4e13ad1b724738a93480314c91e358;a7cb799944684d5faaf36793f7096f73;15.18
Ativos;cb40d3d414664716a5cf2aa4d6ace692;a7cb799944684d5faaf36793f7096f73;-5.34
Liquido;e2308407151a4b3190503e13186cd9d5;a7cb799944684d5faaf36793f7096f73;67.32
Livros;0031a799532343a084419caa0963155c;16a2995a39b04599a996e6e2fd355f71;-90.91
Outras;018dc7ad876e42cd8197f38504c0dcb6;16a2995a39b04599a996e6e2fd355f71;-8.05
...
```


1. A primeira tarefa a ser realizada para poder manipular a estrutura de contas é carregá-la em uma árvore. Você poderá
fazer isso na função `carrega_contas()`, que recebe um ponteiro para um arquivo e retorna um ponteiro para o nó raiz
da árvore.

O código já inclui funções para processar cada linha do arquivo e obter uma estrutura do tipo `Conta` contendo os campos
`nome`, `id`, `id_pai` e `saldo`.

Também está disponível uma função para imprimir de forma a hierarquia da árvore carregada da seguinte forma.

```
\--Root Account                                        -0.54
   |--Liquido                                          67.32
   |  \--Saldos Iniciais                               12.57
   |--Ativos                                           -5.34
   |  \--Ativos Atuais                                 85.78
   |     |--Conta Poupanca                             26.30
   |     |--Conta Corrente                            -84.76
   |     \--Dinheiro na Carteira                       78.68
   |--Passivo                                          15.18
   |  \--Contas a Pagar                                64.09
   |     \--Cartao de Credito                          27.56
   |--Receitas                                        -32.80
   |  |--Outras Receitas                               57.08
   |  |--Juros Recebidos                               13.32
   |  |  |--Juros Conta Poupanca                      -68.72
   |  |  |--Juros Conta Corrente                       -8.66
   |  |  \--Outros Juros                               63.77
   |  |--Bonus                                        -60.09
   |  |--Salario                                       57.88
   |  \--Presentes Recebidos                           99.80
   \--Despesas                                        -13.82
      |--Despesas com Saude                            25.08
      |--Computador                                    42.39
      |--Diversao                                     -51.49
      |  |--Musica/Cinema                              77.99
      |  |--Viagens                                   -16.30
      |  \--Passeios                                   32.79
      |--Taxas Bancarias                              -65.90
      |--Tv por assinatura                              4.01
      |--Transportes Publicos                           0.78
      |--Servicos                                      -0.47
      |  |--Gas                                        48.27
      |  |--Eletricidade                              -80.35
      |  \--Agua                                       94.04
      |--Doacoes                                       57.64
      |--Ajustes                                      -30.81
      |--Telefone                                     -15.01
      |--Passatempos                                  -25.22
      |--Seguro                                        60.53
      |  |--Seguro de Vida                            -65.43
      |  |--Seguro Automovel                           13.73
      |  \--Seguro Saude                              -18.64
      |--Material de Escritorio                       -44.43
      |--Lavandaria                                    80.20
      |--Refeicoes Fora                               -95.05
      |--Automovel                                     56.92
      |  |--Combustivel                                -1.11
      |  |--Estacionamento                             61.71
      |  |--Impostos                                  -36.72
      |  |  |--CPMF                                    86.61
      |  |  |--IRF                                    -56.58
      |  |  |--INSS                                    82.15
      |  |  \--Outros Impostos                         22.28
      |  \--Reparos e Manutencao                       63.10
      |--Educacao                                     -77.86
      |--Internet                                     -57.13
      |--Vestuario                                     88.99
      |--Presentes                                    -35.90
      |--Assinaturas                                   94.39
      |--Mercearia                                     -8.51
      |--Outras                                        -8.05
      \--Livros                                       -90.91
```
