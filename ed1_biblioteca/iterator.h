#ifndef ITERATOR_H
#define ITERATOR_H

#include "base.h"

typedef struct iterator_ iterator_t;
struct iterator_ {
    boolean (*has_more)(iterator_t *itr);
    void *(*get)(iterator_t *itr);
    void (*next)(iterator_t *itr);
    void (*delete)(iterator_t *itr);
};

#define iterator_has_more(itr)  ((iterator_t *) (itr))->has_more(itr)
#define iterator_get(itr)       ((iterator_t *) (itr))->get(itr)
#define iterator_next(itr)      ((iterator_t *) (itr))->next(itr)

void iterator_delete(iterator_t *self);

#endif /* ITERATOR_H */
