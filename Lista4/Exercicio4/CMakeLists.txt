cmake_minimum_required(VERSION 3.10)
project(Exercicio4 C)

set(CMAKE_C_STANDARD 99)

add_executable(lista_ordenada_test lista_ordenada.h lista_ordenada.c lista_ordenada_test.c)

add_executable(lista_test lista.c)

add_executable(lista_circular_test lista_circular.c)

add_custom_target(tests ALL ${CMAKE_BINARY_DIR}/lista_test ${CMAKE_BINARY_DIR}/lista_ordenada_test ${CMAKE_BINARY_DIR}/lista_circular_test
                  DEPENDS lista_test lista_ordenada_test)