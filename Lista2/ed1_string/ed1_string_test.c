#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"

#include "ed1_string.h"

static MunitResult test_strtrim() {
  char buffer[50];

  strtrim(buffer, "   Estruturas de Dados 1    ");
  assert_string_equal("Estruturas de Dados 1", buffer);

  strtrim(buffer, "   Estruturas de Dados 1\t");
  assert_string_equal("Estruturas de Dados 1", buffer);

  strtrim(buffer, " \t\n Estruturas de Dados 1 \t");
  assert_string_equal("Estruturas de Dados 1", buffer);

  strtrim(buffer, " \t\n Estruturas de    Dados 1 \t");
  assert_string_equal("Estruturas de    Dados 1", buffer);

  return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
  {
    (char*) "/ed1_string/strtrim",
    test_strtrim,
    NULL,
    NULL,
    MUNIT_TEST_OPTION_NONE,
    NULL
  },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "",
  /* The first parameter is the array of test suites. */
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

#include <stdlib.h>

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, (void*) "ed1_string", argc, argv);
}
