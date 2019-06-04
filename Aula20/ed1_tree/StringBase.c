//
// Created by gustavosousa on 04/06/19.
//

#include "StringBase.h"
#include <stdlib.h>
#include <string.h>

char *
string_copy(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(sizeof(char) * (len + 1));
    if (result)
        strcpy(result, str);

    return result;
}
