#ifndef CAMINHO_HEADER_GUARD
#define CAMINHO_HEADER_GUARD
#pragma once
#include "grafo.h"

typedef struct Caminho {
    int idVertice;
    float distancia;
    struct Caminho *proximo;
	float distanciaTotal;
} Caminho;



Caminho* CriarCaminho(int idVertice, float distancia);
float DistanciaCaminho(Caminho *caminho);
Caminho* ConcatenarCaminhos(Caminho *caminho1, Caminho *caminho2);
void FreeCaminho(Caminho *caminho);
Caminho* CaminhoUnicoVertice(int origem);
Caminho* ConstruirCaminho(Vertice* grafo, int destino);
void ImprimirCaminho(Caminho* caminho, int centroRecolha);

#endif