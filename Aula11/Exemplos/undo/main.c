#include <gtk/gtk.h>
#include <assert.h>
#include "Pilha.h"
#include "EditorOperacao.h"


static Pilha *undo_pilha = NULL; // mantém pilha de operações realizadas
static Pilha *redo_pilha = NULL; // mantém pilha de operações desfeitas

static gint64 operacao_corrente_inicio = 0; // armazena o momento em que a operação de digitação atual começou
static gint64 operacao_corrente_modificada = 0; // armazena o momento da última tecla na sequencia atual

static EditorOperacao *operacao_corrente = NULL;

static void
empilha_operacao_corrente() {
    g_assert_nonnull(operacao_corrente);
    g_assert(operacao_corrente->inicio != operacao_corrente->fim);

    g_print("PUSH %s \'%s\' [%d %d]\n", operacao_corrente->tipo ? "DEL" : "ADD", operacao_corrente->str->str,
            operacao_corrente->inicio, operacao_corrente->fim);

    pilha_empilha(undo_pilha, operacao_corrente);

    operacao_corrente = NULL;
}

static void
limpa_redo_pilha() {
    while (!pilha_esta_vazia(redo_pilha))
        editor_operacao_libera(pilha_desempilha(redo_pilha));
}

#define INTERVALO_DIGITACAO (1000000 / 2)

static gboolean
deve_iniciar_operacao() {
    gint64 now = g_get_real_time();

    if (operacao_corrente == NULL)
        return TRUE;

    if (now - operacao_corrente_modificada > INTERVALO_DIGITACAO)
        return TRUE;

    if (now - operacao_corrente_inicio > 4 * INTERVALO_DIGITACAO)
        return TRUE;

    return FALSE;
}

static gboolean disable_insert = FALSE;
static gboolean disable_delete = FALSE;

static void
text_inserted(GtkTextBuffer *buffer,
              GtkTextIter *location,
              gchar *text,
              gint len,
              gpointer user_data) {
    // Verifica se o programa está inserindo o texto e não o usuário
    if (disable_insert) {
        return;
    }

    limpa_redo_pilha();

    gint inicio = gtk_text_iter_get_offset(location);
    g_debug("TEXT_INSERTED [%i, %i] = %s\n", inicio, inicio + len, text);

    gint64 now = g_get_real_time();

    if (deve_iniciar_operacao()
        || operacao_corrente->tipo != TEXTO_INSERIDO
        || inicio != operacao_corrente->fim) {
        if (operacao_corrente != NULL)
            empilha_operacao_corrente();

        g_assert(operacao_corrente == NULL);

        operacao_corrente_inicio = g_get_real_time();
        operacao_corrente = editor_operacao_novo(TEXTO_INSERIDO);
        operacao_corrente->inicio = gtk_text_iter_get_offset(location);

        g_string_append(operacao_corrente->str, text);
        operacao_corrente->fim = inicio + len;
    } else {
        g_string_append(operacao_corrente->str, text);
        operacao_corrente->fim += len;
    }

    operacao_corrente_modificada = now;
}

static void
text_deleted(GtkTextBuffer *buffer,
             GtkTextIter *start,
             GtkTextIter *end,
             gpointer user_data) {
    if (disable_delete) {
        return;
    }

    limpa_redo_pilha();
    gint64 now = g_get_real_time();

    gint inicio = gtk_text_iter_get_offset(start);
    gint fim = gtk_text_iter_get_offset(end);
    gchar *str = gtk_text_buffer_get_text(buffer, start, end, TRUE);

    g_debug("TEXT_DELETED [%i, %i] = %s\n", inicio, fim, str);

    if (deve_iniciar_operacao()
        || operacao_corrente->tipo != TEXTO_REMOVIDO
        || inicio != operacao_corrente->inicio) {
        if (operacao_corrente != NULL)
            empilha_operacao_corrente();

        g_assert(operacao_corrente == NULL);

        operacao_corrente_inicio = g_get_real_time();
        operacao_corrente = editor_operacao_novo(TEXTO_REMOVIDO);
        operacao_corrente->inicio = inicio;
        operacao_corrente->fim = fim;
        g_string_append(operacao_corrente->str, str);
    } else {
        g_string_append(operacao_corrente->str, str);
        operacao_corrente->fim += (fim - inicio);
    }

    operacao_corrente_modificada = now;
    g_free(str);
}

static void
aplica_operacao(GtkTextBuffer *buffer, EditorOperacao *operacao) {
    GtkTextIter start, end;
    gtk_text_buffer_get_iter_at_offset(buffer, &start, operacao->inicio);
    gtk_text_buffer_get_iter_at_offset(buffer, &end, operacao->fim);

    if (operacao->tipo == TEXTO_INSERIDO) {
        disable_delete = TRUE;
        gtk_text_buffer_delete(buffer, &start, &end);
        disable_delete = FALSE;

        gtk_text_buffer_get_iter_at_offset(buffer, &start, operacao->inicio);
        gtk_text_buffer_place_cursor(buffer, &start);
    } else if (operacao->tipo == TEXTO_REMOVIDO) {
        disable_insert = TRUE;
        gtk_text_buffer_insert(buffer, &start, operacao->str->str, -1);
        disable_insert = FALSE;

        gtk_text_buffer_get_iter_at_offset(buffer, &end, operacao->fim);
        gtk_text_buffer_place_cursor(buffer, &end);
    } else {
        g_assert(FALSE);
    }
}


static void
undo(GtkTextBuffer *buffer) {
    if (!editor_operacao_vazia(operacao_corrente))
        empilha_operacao_corrente();

    if (pilha_esta_vazia(undo_pilha))
        return;

    EditorOperacao *operacao = pilha_desempilha(undo_pilha);
    g_print("POP  %s\'%s\' [%d %d]\n", operacao->tipo ? "DEL" : "ADD", operacao->str->str, operacao->inicio,
            operacao->fim);

    aplica_operacao(buffer, operacao);

    editor_operacao_inverte(operacao);
    pilha_empilha(redo_pilha, operacao);
}

static void
redo(GtkTextBuffer *buffer) {
    if (pilha_esta_vazia(redo_pilha))
        return;

    EditorOperacao *operacao = pilha_desempilha(redo_pilha);
    aplica_operacao(buffer, operacao);

    editor_operacao_inverte(operacao);
    pilha_empilha(undo_pilha, operacao);
}


static void
imprime_item_pilha(void *data) {
    EditorOperacao *op = data;

    g_print("\t%s\'%s\' [%d %d]\n", op->tipo ? "DEL" : "ADD", op->str->str, op->inicio,
            op->fim);
}

static void
imprime_pilhas() {
    g_print("PILHA UNDO\n");
    pilha_percorre(undo_pilha, imprime_item_pilha);

    g_print("PILHA REDO\n");
    pilha_percorre(redo_pilha, imprime_item_pilha);
}


static void
activate(GtkApplication *app,
         gpointer user_data) {
    undo_pilha = pilha_nova();
    redo_pilha = pilha_nova();

    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Window");
    gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);

    GtkTextView *text_view = GTK_TEXT_VIEW(gtk_text_view_new());
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    g_signal_connect(buffer, "delete-range", G_CALLBACK(text_deleted), NULL);
    g_signal_connect(buffer, "insert-text", G_CALLBACK(text_inserted), NULL);


    GtkAccelGroup *accel_group = gtk_accel_group_new();
    GClosure *ctrl_z = g_cclosure_new_swap(G_CALLBACK(undo), buffer, NULL);
    gtk_accel_group_connect(accel_group, GDK_KEY_Z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE, ctrl_z);

    GClosure *ctrl_y = g_cclosure_new_swap(G_CALLBACK(redo), buffer, NULL);
    gtk_accel_group_connect(accel_group, GDK_KEY_Y, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE, ctrl_y);

    GClosure *ctrl_p = g_cclosure_new_swap(G_CALLBACK(imprime_pilhas), NULL, NULL);
    gtk_accel_group_connect(accel_group, GDK_KEY_P, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE, ctrl_p);


    gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

    gtk_container_add(GTK_CONTAINER (window), GTK_WIDGET(text_view));

    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_widget_show_all(window);
}

int
main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("br.ufg.emc.exemplo", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    return status;
}

