#ifndef FUNC_HEADER_GUARD
#define FUNC_HEADER_GUARD
#include <stdio.h>
#include "clientes.h"
#include "transportes.h"
#include "gestores.h"
#include "transacoes.h"
#include "grafo.h"
#define MAX_CHAR 50

//login 
int IniciarLogin(struct NodeClientes** clientesHead, struct NodeGestores** gestoresHead, int* nifClienteLogado);


// Carregar dados de ficheiros binarios
int CarregarDados(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes,
                    struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes);

int CarregarFicheiroClientes(struct NodeClientes** head, char *nomeFicheiro);
int CarregarFicheiroTransacoes(struct NodeTransacoes** head, char* nomeFicheiro);
int CarregarFicheiroGestores(struct NodeGestores** head, char* nomeFicheiro);
int CarregarFicheiroTransportes(struct NodeTransporte** head, char* nomeFicheiro);
int CarregarBinarioClientes(struct NodeClientes** head);
int CarregarBinarioGestores(struct NodeGestores** head);
int CarregarBinarioTransportes(struct NodeTransporte** head);
int CarregarBinarioTransacoes(struct NodeTransacoes** head);


// Carregar dados de ficheiros CSV
int CarregarCSV(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes, 
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes);
int LerClientesDeFicheiro(struct NodeClientes** headRef, FILE *ficheiro);
int LerTransportesDeFicheiro(struct NodeTransporte** headRef, FILE *ficheiro);
int LerGestoresDeFicheiro(struct NodeGestores** headRef, FILE *ficheiro);
int LerTransacoesDeFicheiro(struct NodeTransacoes** headRef, FILE *ficheiro);

// Menu
int listaMenuGestor();
int ListaMenuCliente();


// Exportar dados para ficheiros binarios
int ExportarClientes(struct NodeClientes* listaClientes);
int ExportarGestores(struct NodeGestores* listaGestores);
int ExportarTransportes(struct NodeTransporte* listaTransporte);
int ExportarTransacoes(struct NodeTransacoes* listaTransacoes);








#endif
