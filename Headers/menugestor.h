#ifndef MENUGESTOR_HEADER_GUARD
#define MENUGESTOR_HEADER_GUARD
#pragma once
#include "verificacoes.h"

int MenuGestor(struct NodeClientes* headClientes, 
               struct NodeGestores* headGestores, 
               struct NodeTransporte* headTransportes, 
               struct NodeTransacoes* headTransacoes,
               Vertice *headVertice);

#endif