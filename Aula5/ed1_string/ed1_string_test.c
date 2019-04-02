/* ed1_string_test.c */
#include <assert.h>
#include <string.h>

#include "ed1_string.h"


void test_trim(void ) {
  char trimmed[50];

  strtrim(trimmed, "    Estruturas de dados 1");
  assert(strcmp("Estruturas de dados 1", trimmed) == 0);

  strtrim(trimmed, "Estruturas de dados 1       ");
  assert(strcmp("Estruturas de dados 1", trimmed) == 0);

  strtrim(trimmed, "Estruturas de dados 1\n\t");
  assert(strcmp("Estruturas de dados 1", trimmed) == 0);

  strtrim(trimmed, "Estruturas\tde\tdados");
  assert(strcmp("Estruturas\tde\tdados", trimmed) == 0);

  strtrim(trimmed, "   Estruturas    de dados");
  assert(strcmp("Estruturas    de dados", trimmed) == 0);
}

void test_reverse(void) {

}

int main(void) {
  test_trim();
  test_reverse();
}
