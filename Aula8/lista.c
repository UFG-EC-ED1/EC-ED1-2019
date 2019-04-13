#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/*
 * Essa implementação trata uma lista como uma sequencia de nós encadeados.
 * Uma lista vazia é representada pelo valor NULL
 */
struct lista_no {
    int valor;
    struct lista_no *seguinte;
};

typedef struct lista_no ListaNo;


/**
 * Aloca um novo nó e define os campos valor e seguinte
 * @param valor
 * @param seguinte
 * @return um novo nó alocado
 */
static ListaNo *
lista_no_novo(int valor, ListaNo *seguinte) {
    ListaNo *novo_no = malloc(sizeof(ListaNo));
    novo_no->valor = valor;
    novo_no->seguinte = seguinte;
    return novo_no;
}

/**
 * Adiciona um elemento ao início da lista.
 * @param cabeca é um ponteiro para o início (cabeça) da lista
 * @param valor é o valor a ser incluído
 * @return um ponteiro para o novo nó que agora é o novo início (cabeça)
 */
ListaNo *
lista_no_adiciona_inicio(ListaNo *cabeca, int valor) {
    // Se a lista é vazia, o parâmetro cabeca, contém NULL
    // e o ponteiro seguinte do novo nó também será NULL
    return lista_no_novo(valor, cabeca);
}


/**
 * Adiciona um elemento ao fim da lista.
 * @param cabeca é um ponteiro par ao início (cabeça) da lista
 * @param valor é o valor a ser incluído
 * @return
 */
ListaNo *
lista_no_adiciona_fim(ListaNo *cabeca, int valor) {
    // Se a cabeca é vazia podemos incluir ao início
    if (cabeca == NULL)
        return lista_no_adiciona_inicio(NULL, valor);

    // Percorremos a lista, até achar o último elemento (onde seguinte é NULL)
    ListaNo *corrente = cabeca;
    while (corrente->seguinte != NULL) {
        corrente = corrente->seguinte;
    }

    // Criamos um novo nó e adicionamos ao fim da lista
    ListaNo *novo_no = lista_no_novo(valor, NULL);
    corrente->seguinte = novo_no;

    return cabeca;

}


/**
 * Remove o primeiro elemento da lista.
 * @param cabeca é um ponteiro par ao início (cabeça) da lista
 * @return um ponteiro para a nova cabeça da lista, ou NULL se a lista está vazia
 */
ListaNo *
lista_no_remove_inicio(ListaNo *cabeca) {
    // Se a lista está vazia retorna NULL
    if (cabeca == NULL)
        return NULL;

    ListaNo *tmp = cabeca;
    cabeca = cabeca->seguinte;
    free(tmp);

    return cabeca;
}

size_t
lista_no_tamanho(ListaNo *cabeca) {
    ListaNo *corrente = cabeca;
    size_t tam = 0;
    while (corrente != NULL) {
        corrente = corrente->seguinte;
        tam++;
    }

    return tam;
}

size_t
litsa_no_tamanho_recursivo(ListaNo *cabeca) {
    if (cabeca == NULL)
        return 0;

    return 1 + litsa_no_tamanho_recursivo(cabeca->seguinte);
}

int
lista_obtem_valor(ListaNo *cabeca, int posicao) {
// Para fazer
}


/**
 * Estrutura de lista que encapsula a estrutura de nos encadeados
 */
struct lista {
    ListaNo *cabeca;    // ponteiro para a cabeça da lista
    size_t qtd;         // qtd de elementos na lista
};

typedef struct lista Lista;

/**
 * Cria uma nova lista vazia.
 * @return
 */
Lista *
lista_novo(void) {
    Lista *lista = malloc(sizeof(Lista));

    lista->cabeca = NULL;
    lista->qtd = 0;

    return lista;
}


/**
 * Inclui um item ao início da lista
 * @param lista
 * @param valor
 */
void
lista_adiciona_inicio(Lista *lista, int valor) {
    // Utiliza função criada anteriormente para manipulação dos nós
    lista->cabeca = lista_no_adiciona_inicio(lista->cabeca, valor);
    lista->qtd++;
}
/**
 * Remove primeiro elemento da lista.
 * @param lista ponteiro para uma lista (gera um erro se a lista está vazia)
 * @return o valor removido
 */
int
lista_remove_inicio(Lista *lista) {
    assert(lista->cabeca != NULL);

    int valor = lista->cabeca->valor;
    lista->cabeca = lista_no_remove_inicio(lista->cabeca);
    lista->qtd--;

    return valor;
}


/**
 * Retorna a quantidade de itens na lista
 * @param lista ponteiro para uma lista
 * @return
 */
size_t
lista_tamanho(Lista *lista) {
    return lista->qtd;
}


int main() {
    ListaNo *lista = NULL; // lista vazia

    lista = lista_no_adiciona_inicio(lista, 5);
    lista = lista_no_adiciona_inicio(lista, 3);
    lista = lista_no_adiciona_inicio(lista, 4);
    lista = lista_no_adiciona_inicio(lista, 7);
    lista = lista_no_adiciona_fim(lista, 10);

    lista = lista_no_remove_inicio(lista);

    printf("%lu\n\n", lista_no_tamanho(lista));
    printf("%lu\n\n", litsa_no_tamanho_recursivo(lista));

    for (ListaNo *no = lista; no != NULL; no = no->seguinte) {
        printf("%d\n", no->valor);
    }

}
