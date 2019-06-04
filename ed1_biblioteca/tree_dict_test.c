
#include "tree_dict.h"
#include <string.h>
#include <stdio.h>


static int
compare_string(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

int main(void) {
    char *palavras[] = {
            "carro", "motor", "escola", "carro", "aluno", "carro", "teste"
    };

    tree_dict_t *dict = tree_dict_new(compare_string);

    for (int i = 0; i < 7; i++) {
        printf("%s\n", palavras[i]);

        int qtd = (int) tree_dict_get(dict, palavras[i]);
        tree_dict_put(dict, palavras[i], (void *) (qtd + 1));
    }

    list_t *keys = tree_dict_keys(dict);
    for (iterator_t *itr = list_iterator(keys); iterator_has_more(itr); iterator_next(itr)) {
        const char *palavra = iterator_get(itr);
        int qtd = (int) tree_dict_get(dict, palavra);

        printf("%s %d\n", palavra, qtd);
    }
}