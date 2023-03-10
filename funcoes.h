#ifndef FUNC_HEADER_GUARD
#define FUNC_HEADER_GUARD

#include <stdio.h>

#include "estruturas.h"
#include "clientes.h"
#include "gestores.h"
#include "transportes.h"
#include "transacoes.h"

#include "menuutilizador.h"
#include "menugestor.h"
enum Estrutura { CLIENTES, TRANSPORTE, GESTORES, TRANSACOES, TESTE };
enum TipoUser { GESTOR, CLIENTE };

//login 
int IniciarLogin(struct NodeClientes** clientesHead, struct NodeGestores** gestoresHead);
//

int CarregarDados(void* head, enum Estrutura tipoEstrutura, char *nomeFicheiro);
int LerClientesDeFicheiro(struct NodeClientes** headRef, FILE *ficheiro);
int LerTransportesDeFicheiro(struct NodeTransporte** headRef, FILE *ficheiro);
int LerGestoresDeFicheiro(struct NodeGestores** headRef, FILE *ficheiro);
int LerTransacoesDeFicheiro(struct NodeTransacoes** headRef, FILE *ficheiro);
//int IniciarLogin(Clientes *clientes, int totalClientes, Gestores *gestores, int totalGestores);
int menu();


// exportar para binario
int ExportarParaBinario(struct NodeClientes* listaClientes, 
                        struct NodeGestores* listaGestores, 
                        struct NodeTransporte* listaTransporte, 
                        struct NodeTransacoes* listaTransacoes, 
                        const char* nomeFicheiro);
char* LerNomeFicheiro();






#endif
