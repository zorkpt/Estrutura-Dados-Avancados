#ifndef MENUGESTOR_HEADER_GUARD
#define MENUGESTOR_HEADER_GUARD
#pragma once
#include "clientes.h"
#include "gestores.h"
#include "transportes.h"
#include "transacoes.h"
#include "grafo.h"

int MenuGestor(struct NodeClientes* headClientes, 
               struct NodeGestores* headGestores, 
               struct NodeTransporte* headTransportes,
               NodeTipoTransporte* headTipoTransporte,
               struct NodeTransacoes* headTransacoes,
               Vertice *headVertice);

#endif