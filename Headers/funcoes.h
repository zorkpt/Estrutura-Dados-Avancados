#ifndef FUNC_HEADER_GUARD
#define FUNC_HEADER_GUARD
#include <stdio.h>
#include "clientes.h"
#include "transportes.h"
#include "gestores.h"
#include "transacoes.h"
#define MAX_CHAR 50

//login 
int IniciarLogin(struct NodeClientes** clientesHead, struct NodeGestores** gestoresHead, int* nifClienteLogado);
//

int CarregarFicheiroClientes(struct NodeClientes** head, char *nomeFicheiro);
int CarregarFicheiroTransacoes(struct NodeTransacoes** head, char* nomeFicheiro);
int CarregarFicheiroGestores(struct NodeGestores** head, char* nomeFicheiro);
int CarregarFicheiroTransportes(struct NodeTransporte** head, char* nomeFicheiro);


int LerClientesDeFicheiro(struct NodeClientes** headRef, FILE *ficheiro);
int LerTransportesDeFicheiro(struct NodeTransporte** headRef, FILE *ficheiro);
int LerGestoresDeFicheiro(struct NodeGestores** headRef, FILE *ficheiro);
int LerTransacoesDeFicheiro(struct NodeTransacoes** headRef, FILE *ficheiro);
int listaMenuGestor();
int ListaMenuCliente();


// exportar para binario
int ExportarClientes(struct NodeClientes* listaClientes);
int ExportarGestores(struct NodeGestores* listaGestores);
int ExportarTransportes(struct NodeTransporte* listaTransporte);
int ExportarTransacoes(struct NodeTransacoes* listaTransacoes);
int CarregarCSV(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes, 
                 struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes);
int CarregarDados(struct NodeClientes** headClientes, struct NodeTransporte** headTransportes,
                    struct NodeGestores** headGestores, struct NodeTransacoes** headTransacoes);
int CarregarBinarioClientes(struct NodeClientes** head);
int CarregarBinarioGestores(struct NodeGestores** head);
int CarregarBinarioTransportes(struct NodeTransporte** head);
int CarregarBinarioTransacoes(struct NodeTransacoes** head);








#endif
