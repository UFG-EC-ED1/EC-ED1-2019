//
// Created by gustavo on 11/06/19.
//

#ifndef ED1_ARVORE_GENERICA_STR_UTIL_H
#define ED1_ARVORE_GENERICA_STR_UTIL_H

#include <stdlib.h>
#include <string.h>

char *
str_copia(const char *str);

int
str_separa_n(char *str, char *sep, char **tokens, size_t n);

void
str_trim(char *destino, const char *origem);

#endif //ED1_ARVORE_GENERICA_STR_UTIL_H
