#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct no_int NoInt;
struct no_int {
    int item;
    NoInt *proximo;
};

NoInt *
no_int_novo(int item, NoInt *proximo) {
    NoInt *no = malloc(sizeof(NoInt));

    no->item = item;
    no->proximo = proximo;

    return no;
}

NoInt *
no_int_adiciona_inicio(NoInt *cabeca, int item) {
    return no_int_novo(item, cabeca);
}

NoInt *
no_int_adiciona_fim(NoInt *cabeca, int item) {
    if (cabeca == NULL)
        return no_int_adiciona_inicio(cabeca, item);

    NoInt *no = cabeca;

    while (no->proximo != NULL)
        no = no->proximo;

    no->proximo = no_int_novo(item, NULL);

    return cabeca;
}

NoInt *
no_int_adiciona(NoInt *cabeca, int posicao, int item) {
  if (cabeca == NULL)
      return no_int_adiciona_inicio(cabeca, item);

  NoInt *no = cabeca;

  while (no->proximo != NULL && posicao-- > 0)
      no = no->proximo;

  no->proximo = no_int_novo(item, NULL);

  return cabeca;
}

NoInt *
no_int_remove_inicio(NoInt *cabeca) {
    if (cabeca == NULL)
        return NULL;

    NoInt *temp = cabeca;
    cabeca = cabeca->proximo;
    free(temp);

    return cabeca;
}

size_t
no_int_tamanho(NoInt *cabeca) {
    if (cabeca == NULL)
        return 0;

    return 1 + no_int_tamanho(cabeca->proximo);
}

NoInt *no_int_obtem(NoInt *lista, int posicao) {

}

NoInt *no_int_inverte(NoInt *lista) {

}

NoInt *no_int_filtro(NoInt *lista, int valor_filtrado) {

}

NoInt *no_int_libera_lista(NoInt *lista) {

}

int
main(void) {
  NoInt *lista = NULL; // lista vazia


  assert(0 == no_int_tamanho(lista));
  assert(NULL == no_int_obtem(lista, 0));

  lista = no_int_adiciona_inicio(lista, 1);
  assert(1 == no_int_obtem(lista, 0)->item);
  lista = no_int_adiciona_inicio(lista, 2);
  lista = no_int_adiciona_inicio(lista, 3);
  assert(3 == no_int_tamanho(lista));

  // Como sempre adicionamos no inicio, o primeiro
  // item deve ser o último que foi adicionado
  assert(3 == no_int_obtem(lista, 0)->item);
  assert(2 == no_int_obtem(lista, 1)->item);
  assert(1 == no_int_obtem(lista, 2)->item);

  // Como há apenas 3 elementos (0-2), a partir da posicao 3
  // o resultado deve ser NULL
  assert(NULL == no_int_obtem(lista, 3));
  assert(NULL == no_int_obtem(lista, 10));

  lista = no_int_inverte(lista);

  // Verifica o resultado da função inverte
  assert(1 == no_int_obtem(lista, 0)->item);
  assert(2 == no_int_obtem(lista, 1)->item);
  assert(3 == no_int_obtem(lista, 2)->item);

  no_int_libera_lista(lista);


  int vetor[] = { 10, 2, 3, 10, 2, 4 };
  lista = NULL; // Cria uma nova lista vazia
  for (int i = 0; i < 6; i++)
    lista = no_int_adiciona_fim(lista, vetor[i]);
  for (int i = 0; i < 6; i++)
    assert(vetor[i] == no_int_obtem(lista, i)->item);

  NoInt *lista_filtrada = no_int_filtro(lista, 2);
  assert(4 == no_int_tamanho(lista_filtrada));

  no_int_libera_lista(lista);
  no_int_libera_lista(lista_filtrada);

  return 0;
}
