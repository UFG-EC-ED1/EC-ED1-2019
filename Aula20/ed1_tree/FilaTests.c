//
// Created by gustavosousa on 04/06/19.
//

#include "Fila.h"
#include <assert.h>

int
main(void) {
    Fila *f = fila_nova();

    for (int i = 0; i < 10; i++)
        fila_adiciona(f, (void *) i);

    assert(!fila_vazia(f));
    assert(10 == fila_tam(f));
    assert(0 == fila_primeiro(f));

    for (int i = 0; i < 10; i++)
        assert((void *) i == fila_remove(f));


    for (int i = 0; i < 10; i++) {
        for (int i = 0; i < 3; i++) {
            fila_adiciona(f, i);
            fila_adiciona(f, i + 1);
            fila_remove(f);
        }

        for (int i = 0; i < 3; i++) {
            fila_adiciona(f, i);
            fila_remove(f);
        }

    }


    fila_libera(f);

}
