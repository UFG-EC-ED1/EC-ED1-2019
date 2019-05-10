#include "base.h"
#include <assert.h>

#define CV(x) ((const void *) x)

int main() {
    assert(general_cmp(CV(10), CV(2)) > 0);

    assert(general_cmp(CV(2), CV(2)) == 0);

    assert(general_cmp(CV(1), CV(30)) < 0);

    assert(general_cmp(CV(-10), CV(30)) < 0);

    assert(general_cmp(CV(-30), CV(30)) < 0);
    assert(general_cmp(CV(30), CV(-30)) > 0);

    return 0;
}
