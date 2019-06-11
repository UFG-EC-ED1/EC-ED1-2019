//
// Created by gustavo on 11/06/19.
//

#ifndef ED1_ARVORE_GENERICA_CONTA_H
#define ED1_ARVORE_GENERICA_CONTA_H

typedef struct {
    char *nome;
    char *id;
    char *id_pai;
    double saldo;
} Conta;


Conta *
conta_nova(const char *nome, const char *id, const char *id_pai, double saldo);

Conta *
conta_le(char *buffer);

void
conta_libera(Conta *conta);

#endif //ED1_ARVORE_GENERICA_CONTA_H
