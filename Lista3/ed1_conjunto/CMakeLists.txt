cmake_minimum_required(VERSION 3.12)
project(ed1_conjunto C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES conjunto.c conjunto_test.c)

add_executable(ed1_conjunto ${SOURCE_FILES})