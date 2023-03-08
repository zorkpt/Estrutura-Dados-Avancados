#ifndef FUNC_HEADER_GUARD
#define FUNC_HEADER_GUARD

#include <stdio.h>

#include "estruturas.h"
#include "menugestor.h"
#include "menuutilizador.h"
#include "clientes.h"

int CarregarDados(void *estrutura, enum Estrutura tipoEstrutura, char *nomeFicheiro);
int LerClientesDeFicheiro(Clientes *cliente, FILE *ficheiro);
int IniciarLogin(Clientes *clientes, int totalClientes, Gestores *gestores, int totalGestores);
int menu();
#endif
