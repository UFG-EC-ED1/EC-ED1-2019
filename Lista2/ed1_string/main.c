/* main.c */
#include <stdio.h>
#include <stdlib.h>

#include "ed1_string.h"

int main(void) {
	char entrada[51];

	if (!fgets(entrada, 50, stdin)) {
		fprintf(stderr, "Erro na leitura\n");
		return -1;
	}

    printf("\'%s\'\n", entrada);
	strtrim(entrada, entrada);
	printf("\'%s\'\n", entrada);

	return 0;
}
