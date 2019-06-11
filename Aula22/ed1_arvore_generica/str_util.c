//
// Created by gustavo on 11/06/19.
//
#include "str_util.h"

char *
str_copia(const char *str) {
    char *result = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(result, str);
    return result;
}

int
str_separa_n(char *str, char *sep, char **tokens, size_t n) {
    int i = 1;

    *tokens = str;
    for (char *cur = str; *cur && i < n; cur++) {
        if (strchr(sep, *cur)) {
            *cur = '\0';
            tokens[i++] = cur + 1;
        }
    }

    return i;
}

#define WHITESPACES " \t\n\r"

#define IS_WHITESPACE(x) strchr(WHITESPACES, (x))

void str_trim(char *destino, const char *origem) {
    while (IS_WHITESPACE(*origem))
        origem++;

    char *last_valid_char = destino - 1;
    for (; *origem; origem++, destino++) {
        if (!IS_WHITESPACE(*origem))
            last_valid_char = destino;

        *destino = *origem;
    }

    *(last_valid_char + 1) = '\0';
}
