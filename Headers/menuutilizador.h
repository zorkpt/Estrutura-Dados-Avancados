#ifndef MENUUTILIZADOR_HEADER_GUARD
#define MENUUTILIZADOR_HEADER_GUARD
#pragma once
#include "clientes.h"
#include "gestores.h"
#include "transportes.h"
#include "transacoes.h"
#include "grafo.h"

int MenuUtilizador(struct NodeClientes* headClientes, struct NodeGestores* headGestores, 
                struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, Vertice* headVertice,
                int nifClienteLogado );
                
#endif