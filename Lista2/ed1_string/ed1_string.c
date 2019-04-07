/* ed1_string.c */
#include "ed1_string.h"
#include <stdlib.h>
#include <string.h>

/* função estática: apenas visível dentro do módulo */
#define WHITESPACES " \t\n\r"

#define IS_WHITESPACE(x) strchr(WHITESPACES, (x))

void strtrim(char *destino, const char *origem) {
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

void strreverse(char *destino, const char *origem) {
	int len = strlen(origem);
  int i = 0;
  while (i < len) {
    destino[i] = origem[len - i - 1];
  }
  destino[len] = '\0';
}

char *strtrim_aloca(const char *origem) {
  size_t len = strlen(origem) + 1;
  char *dest = malloc(sizeof(char) * len);
  if (dest == NULL)
    return NULL;

  strtrim(dest, origem);
  return dest;
}

char *strreverse_aloca(const char *origem) {
  size_t len = strlen(origem) + 1;
  char *dest = malloc(sizeof(char) * len);
  if (dest != NULL)
    strreverse(dest, origem);

  return dest;
}
