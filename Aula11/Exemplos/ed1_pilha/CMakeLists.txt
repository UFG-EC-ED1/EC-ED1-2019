cmake_minimum_required(VERSION 3.12)
project(ed1_pilha C)

set(CMAKE_C_STANDARD 99)

add_executable(ed1_pilha pilha_tests.c pilha_vetor.c pilha_encadeada.c expressao_bem_formada.c)