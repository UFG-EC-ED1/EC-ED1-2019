//
// Created by gustavo on 10/04/19.
//

#ifndef ED1_EDITOROPERACAO
#define ED1_EDITOROPERACAO

#include <glib.h>

typedef enum {
    TEXTO_INSERIDO,
    TEXTO_REMOVIDO,
    QTD_TIPOS_OPERACOES
} EditorOperacaoTipo;

typedef struct editor_operacao {
    EditorOperacaoTipo tipo;
    GString *str;
    gint inicio;
    gint fim;
} EditorOperacao;

#define editor_operacao_vazia(op) ((op)==NULL||(op)->inicio==(op)->fim)

EditorOperacao *
editor_operacao_novo(EditorOperacaoTipo type);

void
editor_operacao_inverte(EditorOperacao *operacao);

void
editor_operacao_libera(EditorOperacao *operacao);


#endif //ED1_EDITOROPERACAO
