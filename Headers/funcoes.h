#ifndef FUNC_HEADER_GUARD
#define FUNC_HEADER_GUARD
#pragma once
#include "transacoes.h"
#include "clientes.h"
#include "transportes.h"
#include "gestores.h"
#include "grafo.h"
#include "fila.h"
#include "caminho.h"
#include "busca.h"


//login 
int IniciarLogin(struct NodeClientes** clientesHead, struct NodeGestores** gestoresHead, int* nifClienteLogado);


// Carregar dados de ficheiros binarios
int CarregarDados(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes,
                    struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes, Vertice **headVertice, NodeTipoTransporte** headTipoTransporte);

int CarregarFicheiroClientes(struct NodeClientes** head, char *nomeFicheiro);
int CarregarFicheiroTransacoes(struct NodeTransacoes** head, char* nomeFicheiro);
int CarregarFicheiroGestores(struct NodeGestores** head, char* nomeFicheiro);
int CarregarFicheiroTransportes(struct NodeTransporte** head, NodeTipoTransporte** headTipo, char* nomeFicheiro);
int CarregarFicheiroGrafo(Vertice **grafo, char *nomeFicheiro);
int CarregarFicheiroTiposTransporte(NodeTipoTransporte** headTipos, char* nomeFicheiro);
int CarregarBinarioClientes(struct NodeClientes** head);
int CarregarBinarioGestores(struct NodeGestores** head);
int CarregarBinarioTransportes(struct NodeTransporte** head);
int CarregarBinarioTransacoes(struct NodeTransacoes** head);

// Carregar dados de ficheiros CSV
int CarregarCSV(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes, 
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes, Vertice **headGrafo, NodeTipoTransporte** headTipoTransporte);
int LerClientesDeFicheiro(struct NodeClientes** headRef, FILE *ficheiro);
int LerTransportesDeFicheiro(struct NodeTransporte** headRef, NodeTipoTransporte** headTipo, FILE *ficheiro);
int LerGestoresDeFicheiro(struct NodeGestores** headRef, FILE *ficheiro);
int LerTransacoesDeFicheiro(struct NodeTransacoes** headRef, FILE *ficheiro);
int LerGrafoDeFicheiro(Vertice **grafo, FILE *ficheiro);
int LerTiposTransporteDeFicheiro(NodeTipoTransporte** headRef, FILE *ficheiro);


// Menu
int listaMenuGestor();
int ListaMenuCliente();


// Exportar dados para ficheiros binarios
int ExportarTodosDados(NodeClientes *headClientes, NodeGestores *headGestores, NodeTransporte *headTransportes, NodeTransacoes *headTransacoes, Vertice *headGrafo);
int ExportarClientes(struct NodeClientes* listaClientes);
int ExportarGestores(struct NodeGestores* listaGestores);
int ExportarTransportes(struct NodeTransporte* listaTransporte);
int ExportarTransacoes(struct NodeTransacoes* listaTransacoes);
int ExportarTiposTransporte(struct NodeTipoTransporte* listaTiposTransporte);
int ExportarViagens(struct Viagem* listaViagem);
int ExportaVertices(Vertice *grafo);
int ExportaAdjacentes(Vertice *grafo);
int CarregarBinarioVertices(Vertice** grafo);
int CarregarBinarioAdjacentes(Vertice* grafo);
int CarregarBinarioViagens(struct Viagem** headViagem);
int CarregarBinarioTiposTransporte(struct NodeTipoTransporte** headTipoTransporte);





#endif
