#ifndef TRANSACOES_HEADER_GUARD
#define TRANSACOES_HEADER_GUARD
#pragma once
#include "transportes.h"

typedef struct Transacoes{
    int idTransacao;
    int idClienteAAlugar;
    int idTransporte;
    int tempoAlugado;
    int ativo;
} Transacoes;

typedef struct NodeTransacoes
{
    struct Transacoes transacoes;
    struct NodeTransacoes *proximo;

}NodeTransacoes;


int InserirTransacoes(struct NodeTransacoes** headRef, struct Transacoes transacoes);
int MostrarTransacoes(struct NodeTransacoes* head);
int MostrarTransacoesCliente(struct NodeTransacoes* head, int idCliente);
int EditarTransacao(struct Transacoes * transacao, int tempoAlugado, int idClienteAAlugar, int idTransporte);
int RemoverTransacao(struct NodeTransacoes **head, int idTransacao);
struct Transacoes* ProcurarTransacao(struct NodeTransacoes* head, int idTransacao);
int ProximoIDTransacao(struct NodeTransacoes* headTransacoes);
int MostrarHistoricoAlugueres(struct NodeTransacoes* headTransacoes, int nif);
int ClienteEmTransporte(struct NodeTransacoes* headTransacoes, int nif);
int TerminarAluguer(struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, int nifClienteLogado);
int AtualizarEstadoTransporte(struct Clientes* cliente, struct NodeTransporte* headTransportes, 
                            struct NodeTransacoes* headTransacoes, int idTransporte, 
                            int tempoAluguer, float custoTotal, int novoIdTransacao);

#endif