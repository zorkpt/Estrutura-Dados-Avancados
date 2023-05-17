#ifndef CAMINHO_HEADER_GUARD
#define CAMINHO_HEADER_GUARD
#pragma once


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



#endif