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
}Vertice;

typedef struct Caminho {
    int idVertice;
    float distancia;
    struct Caminho *proximo;
} Caminho;

// Definição do tipo Fila
typedef struct Fila {
    struct NoFila *front;
    struct NoFila *rear;
} Fila;

// Definição do tipo NoFila
typedef struct NoFila {
    Vertice *vertice;
    struct NoFila *proximo;
} NoFila;

Adjacente *CriaAdjacente(int idVertice, float distancia);
Vertice* InsereVertice(Vertice *grafo, Vertice* novo);
Vertice* CriarVertice(int idVertice, char cidade[]);
void PrintGrafo(Vertice *grafo);
Vertice* InsereAdjacente(Vertice *grafo, int origem, int destino, float distancia);
void read_csv_file(char *filename, Vertice **graph);
int location_exists(Vertice *graph, int location_id);
const char* GetLocationName(Vertice *grafo, int location_id);	
NodeTransporte *BuscarTransporteMaisProximo(NodeTransporte *listaTransportes, Vertice *grafo, int localCliente);
Vertice *encontrarVertice(Vertice *grafo, int idVertice);
int contarVertices(Vertice *grafo);
int estaVazia(Fila *fila);
Vertice* desenfileirar(Fila *fila);
void enfileirar(Fila *fila, Vertice *vertice);
Caminho* BuscaEmLargura(Vertice *grafo, int origem, int destino);
const char* GetLocationName(Vertice *grafo, int location_id);
int location_exists(Vertice *graph, int location_id);
Fila* CriarFila();
Vertice* BuscarVertice(Vertice *grafo, int idVertice);
Caminho* MenorCaminho(Vertice *grafo, int origem, int destino);
float DistanciaEntreVertices(Vertice *grafo, int origem, int destino);



#endif