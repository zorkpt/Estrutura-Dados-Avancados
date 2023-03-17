#ifndef MENUUTILIZADOR_HEADER_GUARD
#define MENUUTILIZADOR_HEADER_GUARD
#pragma once
#include "funcoes.h"


int MenuUtilizador(struct NodeClientes* headClientes, struct NodeGestores* headGestores, 
                struct NodeTransporte* headTransportes, struct NodeTransacoes* headTransacoes, 
                int nifClienteLogado );
                
#endif