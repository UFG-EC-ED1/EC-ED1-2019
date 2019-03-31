#include <stdio.h>

#define MAX_SIZE 61

int main(void) {
    int n_entradas;
    int i_proximo_calc = 2;

    unsigned long long fibonacci[MAX_SIZE];
    fibonacci[0] = 0;
    fibonacci[1] = 1;

    scanf("%d", &n_entradas);

    while (n_entradas-- > 0) {
        int x;
        scanf("%d", &x);

        while (i_proximo_calc <= x) {
            fibonacci[i_proximo_calc] =
                    fibonacci[i_proximo_calc - 1] + fibonacci[i_proximo_calc - 2];
            i_proximo_calc++;
        }

        printf("Fib(%d) = %llu\n", x, fibonacci[x]);
    }

    return 0;

}
