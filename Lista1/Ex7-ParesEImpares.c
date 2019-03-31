#include <stdio.h>
#include <stdlib.h>


int compare_ints(int a, int b) {
    int cmp_par_impar = a % 2 - b % 2;
    if (cmp_par_impar != 0)
        return cmp_par_impar;

    return a % 2 == 0 ? a - b : b - a;
}

int compare_int_ptrs(const void *ap, const void *bp) {
    int a = *((int *) ap);
    int b = *((int *) bp);

    return compare_ints(a, b);
}

int main(void) {
    unsigned int n, i;

    scanf("%u", &n);
    int vetor[n];

    for (i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    qsort(vetor, n, sizeof(int), compare_int_ptrs);

    for (i = 0; i < n; i++) {
        printf("%d\n", vetor[i]);
    }

    return 0;
}
