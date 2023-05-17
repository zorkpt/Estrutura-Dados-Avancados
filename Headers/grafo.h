#ifndef GRAFO_HEADER_GUARD
#define GRAPO_HEADER_GUARD
#pragma once
#define MAX_ID 100

#include <stdio.h>


typedef struct Adjacente {
	int idVertice;
	float distancia;
	struct Adjacente *proximo;
}Adjacente;


// ESTRUTURA GRAFO
typedef struct Vertice{
	int idVertice;
	char cidade[MAX_ID];
	struct Vertice *proximo;
	struct Adjacente *adjacentes;
	int visitado;
	int predecessor;
    float distancia;
	int numAdjacentes;
	int idCentroRecolha;
}Vertice;


// CONFIRMADAS
Vertice* CriarVertice(int idVertice, char cidade[]);
Vertice* InsereVertice(Vertice *grafo, Vertice* novo);
Adjacente *CriaAdjacente(int idVertice, float distancia);
Vertice* InsereAdjacente(Vertice *grafo, int origem, Adjacente* novoAdjacente);
const char* GetNomeLocal(Vertice *grafo, int location_id);	
void LimparCamposGrafo(Vertice *grafo);
void PrintGrafo(Vertice *grafo);
Vertice* ProcuraVertice(Vertice *grafo, int idVertice);
void ListarLocais(Vertice *headVertice);
#endif