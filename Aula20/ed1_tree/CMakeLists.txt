cmake_minimum_required(VERSION 3.14)
project(ed1_tree C)

set(CMAKE_C_STANDARD 99)

add_executable(ed1_tree Pilha.h No.h No.c Pilha.c Base.h NoBinario.h NoBinario.c ArvoreGenerica.h ArvoreBinaria.c ArvoreBinaria.h Fila.h Fila.c FilaTests.c StringBase.h StringBase.c ArvoreBinariaBusca.h ArvoreBinariaBusca.c)

add_executable(FilaTests FilaTests.c Fila.c No.c)
add_executable(ArvoreBinariaBuscaTests ArvoreBinariaBuscaTests.c ArvoreBinariaBusca.c ArvoreBinaria.c Fila.c Pilha.c NoBinario.c No.c)


add_executable(ex1 ex1.c)
add_executable(ex2 ex2.c)
add_executable(ex3 ex3.c Pilha.c No.c)
