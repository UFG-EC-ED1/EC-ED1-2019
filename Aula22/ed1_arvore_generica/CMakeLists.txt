cmake_minimum_required(VERSION 3.14)
project(ed1_arvore_generica C)

set(CMAKE_C_STANDARD 99)
add_compile_options("$<$<CONFIG:DEBUG>:-DNDEBUG>")
add_executable(arvore_generica main.c conta.c no_lista.c str_util.c)
add_executable(arvore_generica_pronto main_pronto.c conta.c no_lista.c str_util.c)
