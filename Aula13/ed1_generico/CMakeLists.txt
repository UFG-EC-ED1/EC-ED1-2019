cmake_minimum_required(VERSION 3.10)
project(ed1_generico C)

set(CMAKE_C_STANDARD 99)

add_executable(lista_ordenada_test lista_ordenada_test.c lista_ordenada.c aluno.c)