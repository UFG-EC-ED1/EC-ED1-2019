cmake_minimum_required(VERSION 3.12)
project(undo C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Pilha.c EditorOperacao.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})


add_executable(undo ${SOURCE_FILES})
target_link_libraries(undo ${GTK3_LIBRARIES})