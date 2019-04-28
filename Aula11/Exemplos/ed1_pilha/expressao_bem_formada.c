#include "pilha_encadeada.h"
#include "expressao_bem_formada.h"

// Exemplo adaptado do livro de Algoritmos do Prof. Paulo Feofiloff
// Verifica uma expressão contendo parênteses/colchetes/chaves
// {X * [(X + Y) / (J - 3)] + Y}
bool
expressao_bem_formada(char s[]) {
    Pilha *pilha = pilha_nova();

    for (int i = 0; s[i] != '\0'; i++) {
        int c;

        switch (s[i]) {
            case '(':
            case '[':
            case '{':
                pilha_empilha(pilha, s[i]);
                break;

            case ')':
                if (pilha_esta_vazia(pilha))
                    return false;
                c = pilha_desempilha(pilha);
                if (c != '(')
                    return false;
                break;
            case ']':
                if (pilha_esta_vazia(pilha))
                    return false;
                c = pilha_desempilha(pilha);
                if (c != '[')
                    return false;
                break;
            case '}':
                if (pilha_esta_vazia(pilha))
                    return false;
                c = pilha_desempilha(pilha);
                if (c != '{')
                    return false;
                break;
            default:
                continue;
        }

    }
    return pilha_esta_vazia(pilha); // pilha deve estar vazia ao fim da execução
}




bool
expressao_bem_formada_vetor(char s[]) {
    char pilha[200];
    int topo = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char c;

        switch (s[i]) {
            case '(':
            case '[':
            case '{':
                pilha[topo++] = s[i];
            case ')':
                if (topo == 0) // pilha vazia
                    return false;
                c = pilha[--topo];
                if (c != '(')
                    return false;
                break;
            case ']':
                if (topo == 0)
                    return false;
                c = pilha[--topo];
                if (c != '[')
                    return false;
                break;
            case '}':
                if (topo == 0)
                    return false;
                c = pilha[--topo];
                if (c != '{')
                    return false;
                break;
            default:
                continue;
        }
    }
    return topo == 0; // pilha deve estar vazia ao fim da execução
}

