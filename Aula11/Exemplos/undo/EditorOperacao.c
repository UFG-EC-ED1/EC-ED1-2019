//
// Created by gustavo on 10/04/19.
//
#include "EditorOperacao.h"
EditorOperacao *
editor_operacao_novo(EditorOperacaoTipo type) {
    EditorOperacao *cur_op = g_malloc(sizeof(EditorOperacao));
    cur_op->str = g_string_new("");
    cur_op->tipo = type;
    cur_op->inicio = 0;
    cur_op->fim = 0;
    return cur_op;
}

void
editor_operacao_inverte(EditorOperacao *operacao) {
    operacao->tipo = (operacao->tipo + 1) % QTD_TIPOS_OPERACOES;
}

void
editor_operacao_libera(EditorOperacao *my_op) {
    g_string_free(my_op->str, TRUE);
    g_free(my_op);
}
