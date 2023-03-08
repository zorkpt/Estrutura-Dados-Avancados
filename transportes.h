#ifndef TRANSPORTES_HEADER_GUARD
#define TRANSPORTES_HEADER_GUARD
#include "estruturas.h"

int VerTodosTransportes(Transporte *transporte, int totalTransportes);
int VerTransportesDisponiveis(Transporte *transporte, int totalTransporte, Transacoes *transacoes, int totalTransacoes);

#endif