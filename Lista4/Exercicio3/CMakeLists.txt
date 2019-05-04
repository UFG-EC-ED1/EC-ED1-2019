cmake_minimum_required(VERSION 3.10)
project(Exercicio3 C)

set(CMAKE_C_STANDARD 99)

#add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/test
#        COMMAND ${CMAKE_SOURCE_DIR}/main
#        DEPENDS ${CMAKE_SOURCE_DIR}/main
#        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

#add_custom_target(test ${CMAKE_SOURCE_DIR}/main)

set(PROJECT_SOURCES lista_ordenada.c)
set(TEST_SOURCES main.c)

add_executable(main ${PROJECT_SOURCES} ${TEST_SOURCES})

add_custom_target(tests
        COMMAND ${CMAKE_SOURCE_DIR}/main
        DEPENDS ${CMAKE_SOURCE_DIR}/main
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})