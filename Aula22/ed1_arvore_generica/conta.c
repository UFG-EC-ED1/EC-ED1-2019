//
// Created by gustavo on 11/06/19.
//
#include <stdlib.h>
#include "conta.h"
#include "str_util.h"


Conta *
conta_nova(const char *nome, const char *id, const char *id_pai, double saldo) {
    Conta *conta = malloc(sizeof(Conta));
    conta->nome = str_copia(nome);
    conta->id = str_copia(id);
    conta->id_pai = str_copia(id_pai);
    conta->saldo = saldo;
    return conta;
}

Conta *
conta_le(char *buffer) {
    char *partes[4];

    str_trim(buffer, buffer);
    str_separa_n(buffer, ";", partes, 4);

    return conta_nova(partes[0], partes[1], partes[2], strtod(partes[3], NULL));
}

void
conta_libera(Conta *conta) {
    free(conta->nome);
    free(conta->id);
    free(conta->id_pai);
    free(conta);
}
