//
// Created by gustavo on 04/06/19.
//

#ifndef ED1_TREE_ARVORE_BINARIA_ITERATOR_H
#define ED1_TREE_ARVORE_BINARIA_ITERATOR_H


typedef struct {
    Pilha *p;
    NoBinario *cur;
} ArvoreBinariaIterator;

ArvoreBinariaIterator *
ab_inorder(ArvoreBinariaBusca *abb) {
    ArvoreBinariaIterator *itr = malloc(sizeof(ArvoreBinariaIterator));
    itr->p = pilha_nova();
    itr->cur = abb->raiz;

    while (itr->cur != NULL) {
        pilha_push(itr->p, itr->cur);
        itr->cur = itr->cur->esq;
    }

    if (!pilha_vazia(itr->p))
        itr->cur = pilha_pop(itr->p);

    return itr;
}

bool
ab_iterator_has_more(ArvoreBinariaIterator *itr) {
    return itr->cur != NULL;
}

void
ab_iterator_incr(ArvoreBinariaIterator *itr) {

}


#endif //ED1_TREE_ARVORE_BINARIA_ITERATOR_H
