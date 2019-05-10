cmake_minimum_required(VERSION 3.12)
project(ed1_biblioteca C)

set(CMAKE_C_STANDARD 99)

add_library(ed1_biblioteca base.c bst.c iterator.c list.c red_black.c stack.c tree_dict.c)


add_executable(base_test base.c base_test.c)
add_executable(list_test base.c iterator.c list.c list_test.c)
add_executable(bst_test base.c bst.c bst_test.c)
add_executable(red_black_test base.c red_black.c red_black_test.c)
add_executable(stack_test base.c list.c stack.c stack_test.c)
add_executable(tree_dict_test base.c list.c red_black.c tree_dict.c tree_dict_test.c)