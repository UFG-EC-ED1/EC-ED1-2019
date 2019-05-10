#include "iterator.h"

#include <stdlib.h>

void iterator_delete(iterator_t *self) {
    if (self->delete)
        self->delete(self);

    free(self);
}
