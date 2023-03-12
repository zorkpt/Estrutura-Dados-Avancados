#ifndef MENUGESTOR_HEADER_GUARD
#define MENUGESTOR_HEADER_GUARD
#include "../Controller/funcoes.h"

int MenuGestor(struct NodeClientes* headClientes, 
               struct NodeGestores* headGestores, 
               struct NodeTransporte* headTransportes, 
               struct NodeTransacoes* headTransacoes);

#endif