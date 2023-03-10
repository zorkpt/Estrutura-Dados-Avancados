#ifndef TRANSACOES_HEADER_GUARD
#define TRANSACOES_HEADER_GUARD
#include "estruturas.h"


typedef struct Transacoes{
    int idClienteAAlugar;
    int idTransporte;
    int tempoAluguerDecorrido;
} Transacoes;

typedef struct NodeTransacoes
{
    struct Transacoes transacoes;
    struct NodeTransacoes *proximo;
}NodeTransacoes;


void InserirTransacoes(struct NodeTransacoes** headRef, struct Transacoes transacoes);
void MostrarTransacoes(struct NodeTransacoes* head);


#endif