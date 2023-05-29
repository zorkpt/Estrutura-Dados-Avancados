#ifndef GRAFO_HEADER_GUARD
#define GRAPO_HEADER_GUARD
#pragma once
#include <stdio.h>

#define MAX_ID 100

// Estrutura Adjacente
typedef struct Adjacente {
	int idVertice;
	float distancia;
	struct Adjacente *proximo;
}Adjacente;

// Estrutura Vertice
typedef struct Vertice{
	int idVertice;
	char cidade[MAX_ID];
	struct Vertice *proximo;
	struct Adjacente *adjacentes;
	int visitado; // Usado para o algoritmo de Dijkstra
	int predecessor; // Usado para o algoritmo de Dijkstra
	float distancia; // Usado para o algoritmo de Dijkstra
	int numAdjacentes; // Usado para o algoritmo de Dijkstra
	int idCentroRecolha; // Usado para o algoritmo de GreedySearch
}Vertice;

// Funções associadas à estrutura Vertice
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
