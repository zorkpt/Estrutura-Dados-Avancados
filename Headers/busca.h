#ifndef BUSCA_HEADER_GUARD
#define BUSCA_HEADER_GUARD
#pragma once
#include "transportes.h"
#include "fila.h"
#include "grafo.h"
#include <stdio.h>


Caminho* GreedySearch(NodeTransporte *transportes, Vertice *grafo, int centroRecolha);
Caminho* Dijkstra(Vertice *grafo, int origem, int destino);
int ExistemTransportesNaoVisitados(NodeTransporte *transportes);
int ProcurarCentroRecolha(struct Vertice* headGrafo);



#endif