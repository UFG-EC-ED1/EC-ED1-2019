### Modularização

Até agora trabalhamos sempre com a criação de um programa que possui uma função ``main()`` e resolve um determinado problema. No entanto, quando começamos a resolver problemas mais complexos torna-se inviável manter todo o código em uma função ou até mesmo em um único arquivo. É preciso dividir o problema em partes de modo a facilitar a solução do problema, a compreensão e manutenção do código.

A criação de módulos em C é feita por meio de dois arquivos, o que permite separar a definição da implementação do módulo. O arquivo de cabeçalho  (*header*) define os protótipos (interfaces) das funções e os tipos de dados utilizados por essas funções. Dessa forma, módulos externos tem acesso apenas à definição das funções, independente da forma como elas são implementadas ou variáveis/funções internas, específicas do módulo. Já o arquivo de código inclui a implementação das funções e/ou tipos declarados no cabeçalho, além de funções, variáveis, constantes e tipos internos ao módulo.

Os arquivos abaixo ilustram a declaração e definição de um módulo ``ed1_string`` e como este pode ser utilizado por um programa.

```C
/* ed1_string.h */
#ifndef __ED1_STRING_H__
#define __ED1_STRING_H__

void strtrim(char *destino, const char *origem);
void strreverse(char *destino, const char *origem);

#endif
```
> A declaração de um arquivo de cabeçalho é sempre cercada por expressões "guardas" (``#ifndef``/``#define``) que verificam se um símbolo já foi definido ou não. Isso tem como objetivo prevenir que um cabeçalho seja incluído mais de uma vez, o que geraria um erro por declarações duplicadas.


```C
/* ed1_string.c */
#include "ed1_string.h"
#include <stdlib.h>
#include <string.h>

/* função estática: apenas visível dentro do módulo */
static internal_function() {
	/* implementação */
}

void strtrim(char *destino, const char *origem) {
	/* implementação */
}

void strreverse(char *destino, const char *origem) {
	/* implementação */
}
```

```C
/* main.c */
#include <stdio.h>
#include <stdlib.h>

#include "ed1_string.h"

int main(void) {
	char entrada[51];

	if (!fgets(entrada, 50, stdin)) {
		fprintf(stderr, "Erro na leitura\n");
		return -1
	}

	strtrim(entrada, entrada);

	printf("%s\n", entrada);

	return 0;
}
```
>#### Compilação e ligação
>
>Quando trabalhamos com múltiplos módulos é preciso que eles sejam compilados separadamente e depois ligados para gerar um executável ou um arquivo de biblioteca. Abaixo há um exemplo de como podemos compilar o programa acima. O comando ``gcc -c`` gera um arquivo ``.o`` que contém o código compilado do módulo. O último comando recebe como entrada os módulos já compilados e executa a ligação para gerar um executável.
>
>```console
>$ gcc -c ed1_string.c
>$ gcc -c main.c
>$ gcc ed1_string.o main.o -o main
>```
> A execução de vários comandos geralmente é facilitada pelo uso de ferramentas de construção que automatizam o processo. O mais simples é o uso de Makefiles, mas atualmente uma ferramenta muito utilizada tem sido o CMake. Algumas IDEs também podem já automatizar essa tarefa.
