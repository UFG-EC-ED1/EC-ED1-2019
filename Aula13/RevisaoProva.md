## TADs
```C
// Lista
void lista_adiciona(lista_t *lista, size_t posicao, void *item);
void lista_adiciona_fim(lista_t *lista, void *item);
void *lista_obtem(lista_ t *lista, size_t posicao);
size_t lista_tamanho(lista_t *lista);

// Conjunto
void conjunto_adiciona(conjunto_t *conjunto, void *elemento);
bool conjunto_contem(conjunto_t *conjunto, void *elemento);
void *conjunto_remove(conjunto_t *conjunto, void *elemento);
size_t conjunto_tamanho(conjunto_t *conjunto);

// Dicionario
void dicionario_define(dicionario_t *dicionario, void *chave, void *valor);
void *dicionario_obtem(dicionario_t *dicionario, void *chave);
void *dicionario_remove(dicionario_t *dicionario, void *chave);

// Fila
void fila_adiciona(fila_t *fila, void *item);
void *fila_remove(fila_t *fila);
bool fila_vazia(fila_t *fila)

// Pilha
void pilha_empilha(pilha_t *pilha, void *item);
void *pilha_topo(pilha_t *pilha);
void *pilha_desempilha(pilha_t *pilha);
bool pilha_vazia(pilha_t *pilha);
```

Para cada problema abaixo indique qual o tipo de dados pode ser utilizado para auxiliar sua solução e explique com suas palavras a ideia da solução.

1. Dado um artigo (uma lista de palavras), encontrar as 10 palavras mais utilizadas.

2. Dado um vetor *v* e um número *k* verificar se existem dois números em *v* cuja soma é *k*.

3. Implementar as funções desfazer e refazer em um editor de texto.


## Nós encadeados

Nas questões abaixo, uma lista é considerada como uma sequência de nós encadeados, de acordo com a estrutura abaixo.

```C
typedef struct lista_no ListaNo;
struct lista_no {
  int item;
  ListaNo *prox;
};
```

Em alguns casos consideramos que as listas estão previamente ordenadas.

**[Média]** Escreva uma função que calcule a média dos valores em uma lista de nós encadeados.
```C
double media(ListaNo *cabeca);
```

---
**[Máximo recursivo]** Escreva uma função recursiva que retorne o maior item em uma lista de nós encadeados.
```C
int maximo(ListaNo *cabeca);
```
---

**[Remove duplicados]** Considerando uma estrutura de nós encadeados, escreva uma função que recebe uma lista ordenada e remove os itens duplicados. Por exemplo, dada uma lista contendo os itens ``[1, 2, 2, 4, 10, 10, 12]``, a função modifica a lista para conter apenas os itens ``[1, 2, 4, 10, 12]``.

```C
ListaNo *remove_duplicados(ListaNo *cabeca) {
  if (cabeca == NULL)
    return NULL;

  ListaNo *anterior = cabeca;  
  ListaNo *corrente = anterior->prox;
  while (corrente != NULL) {
    if (corrente->item == anterior->item) {     
       anterior->prox = corrente->prox;
       free(corrente);
    } else {
       anterior = corrente;
    }
    corrente = anterior->prox;
  }
}
```


---
**[Concatenação]** Escreva uma função que recebe duas listas, e retorna uma lista única, contendo os itens da primeira lista, seguidos pelos itens da segunda lista. Por exemplo, dadas as listas ``[2, 3, 1, 10, 5]`` e ``[3, 11, 12]`` a função deve retornar uma lista contendo os itens ``[2, 3, 1, 10, 5, 3, 11,12]``.
```C
ListaNo *concatena(ListaNo *a, ListaNo *b) {
	if (a == NULL)
	  return b;
	if (b == NULL)
	  return a;

	No *no = a;
	while (no->prox != NULL)
		no = no->prox;

    no->prox = b;
    return a;
}
```
> A função não deve alocar novos nós, a concatenação deve ser feita utilizando os nós já alocados.
---
**[Merge]** Escreva uma função que recebe duas listas ordenadas e retorne uma nova lista contendo os itens das duas listas também ordenados. Por exemplo, dadas as listas  ``[1, 3, 5, 10]`` e ``[1, 2, 4, 12]`` a função deve retornar uma lista contendo os itens em ordem ``[1, 2, 3, 4, 5, 10, 12]``
```C
ListaNo *merge(ListaNo *a, ListaNo *b);
```
> A função não deve alocar novos nós, o *merge* deve ser feito utilizando os nós já alocados.

---

**[Remove último]** Escreva uma função que remova a última ocorrência de um determinado item. Por exemplo, se desejamos remover a última ocorrência do item ``2`` da lista ``[3, 2, 4, 2, 5, 10]``, obteremos a lista ``[3, 2, 4, 5, 10]``.
```C
ListaNo *remove_ultimo(ListaNo *cabeca, int item);
```
---
**[Tipos de operações]** Para cada uma das operações acima, classifique as como operações de *leitura*, *produção* ou *modificação*.



## Encontre o erro
Todos os trechos de código abaixo contém algum erro de lógica (não realizam a operação descrita) ou podem gerar um erro durante a execução (manipulação incorreta de ponteiros e condições). Identifique o problema no código e proponha uma forma de corrigí-lo.


### Nós encadeados
```C
typedef struct lista_no ListaNo;
struct lista_no {
  int item;
  ListaNo *prox;
};
```

 ```C
 /* Obtém o item na posição (posicao) da lista que se inicia em (cabeca) */
 NoInt *no_int_obtem(NoInt *cabeca, int posicao) {
    NoInt *no = cabeca;
    while (no != NULL) {
        if (no->item == item)
            return no;
        else
            no = no->prox;
    }
    return NULL;
}
 ```

```C
/* Remove a primeira ocorrência do (item) na lista iniciada em (cabeca) */
NoInt *no_int_remove(NoInt *cabeca, int item) {
	if (cabeca == NULL)
		return NULL;

	NoInt *no = cabeca;
	while (no != NULL) {
		if (no->item == item) {
			NoInt *aux = no;
			no->proximo = aux->proximo
			free(aux);
			break;
		}
		no = no->prox;
	}
	return cabeca;
}
```

### Pilha em vetor
```C
#define TAMANHO_MAX 50
typedef struct {
  int vetor[TAMANHO_MAX];
  int topo;
} Pilha;

Pilha *pilha_nova(void) {
  Pilha *pilha = malloc(sizeof(Pilha));
  pilha->topo = -1;
  return pilha;
}
```

```C
void pilha_empilha(Pilha *pilha, int item) {
  pilha[pilha->topo] = item;
  pilha++;
}
```

## Interpretação do código

Identifique o comportamento de cada uma das funções abaixo. Execute a função nas entradas fornecidas e escreva o resultado obtido. Descreva com suas palavras a operação executada pela função.

```C
// Entrada: [1, 3, 2, 1, 5, 4, 2, 3, 5, 10], 4
NoInt *funcao1(NoInt *cabeca, int val) {
  if (cabeca == NULL)
    return NULL;

  while (cabeca->item < val) {
    NoInt *no = cabeca;
    cabeca = cabeca->prox;
    free(no);
  }

  NoInt *anterior = cabeca;
  while (anterior != NULL && anterior->prox != NULL) {
    NoInt *no = anterior->prox;
    if (no->item < val) {
      anterior->prox = no->prox;
      free(no);
    }
  }
  return cabeca;
}
```


```C
// Entrada: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
NoInt *funcao2(NoInt *cabeca) {
  if (cabeca == NULL)  
      return NULL;  

  NoInt *no = cabeca;  
  for (int n = 1; no != NULL; n++) {  
      NoInt *prox = no->prox;  
      for (int i = 0; i < n; i++) {  
          if (prox != NULL) {  
              NoInt *tmp = prox;  
              prox = prox->prox;  
              free(tmp);  
          }  
      }  
      no->prox = prox;  
      no = no->prox;  
  }  
  return cabeca;
}
```
