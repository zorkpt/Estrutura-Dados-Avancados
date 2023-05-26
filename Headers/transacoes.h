#ifndef TRANSACOES_HEADER_GUARD
#define TRANSACOES_HEADER_GUARD
#pragma once
#include "transportes.h"
#include "caminho.h"
#include "grafo.h"

typedef struct Transacoes{
    int idTransacao;
    int idClienteAAlugar;
    int idTransporte;
    int tempoAlugado;
    int ativo; // 0 - Terminado, 1 - Em transporte
} Transacoes;

typedef struct NodeTransacoes {
    struct Transacoes transacoes;
    struct NodeTransacoes *proximo;
}NodeTransacoes;

// Funções para manipulação da estrutura Transacoes
int InserirTransacoes(struct NodeTransacoes** headRef, struct Transacoes transacoes);
int MostrarTransacoes(struct Vertice* grafo, Viagem* headViagens);
int MostrarTransacoesCliente(struct NodeTransacoes* head, int idCliente);
int EditarTransacao(struct Transacoes * transacao, int tempoAlugado, int idClienteAAlugar, int idTransporte);
int RemoverTransacao(struct NodeTransacoes **head, int idTransacao);
struct Transacoes* ProcurarTransacao(struct NodeTransacoes* head, int idTransacao);
int ProximoIDTransacao(struct NodeTransacoes* headTransacoes);

// Funções para operações relacionadas às transações
int ClienteEmTransporte(struct NodeTransacoes* headTransacoes, int nif);
int TerminarAluguer(struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, struct NodeClientes* headClientes, int nifClienteLogado, int idLocalTermino, Caminho* caminho);
Viagem* CriarNovaViagem(int idTransporte, int origem, int destino, float valorPago, float custoPorKm, float distancia, char tipoTransporte[]);

// Funções para atualização de estados
int AtualizarEstadoTransporte(struct Clientes* cliente, struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, int idTransporte, int novoIdTransacao);
void AtualizaSaldoCliente(struct Clientes* cliente, float valor);
void MudaEstadoTransporte(struct Transporte* transporte);
void AtualizaNivelBateria(Transporte *transporte, int bateriaPerdida);
void AtualizaLocalTransporte(struct Transporte* transporte, int novoLocal);
void AtualizaLocalCliente(struct Clientes* cliente, int novoLocal);

// Funções utilitárias
int CalculaBateriaPerdida(float distancia);
float CalculaValorTotal(float distancia, float preco);
int VerificaSePodeAlugar(NodeTransacoes *headTransacoes, struct Clientes *cliente, int nifClienteLogado );

#endif
