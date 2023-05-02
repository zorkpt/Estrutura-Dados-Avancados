#ifndef GRAFO_HEADER_GUARD
#define GRAPO_HEADER_GUARD
#pragma once

#define MAX_ID 100
#include "transportes.h"
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
}Vertice;

typedef struct Caminho {
    int idVertice;
    float distancia;
    struct Caminho *proximo;
} Caminho;

// Definição do tipo Fila
typedef struct Fila {
    struct NodeFila *front;
    struct NodeFila *rear;
} Fila;

// Definição do tipo NodeFila
typedef struct NodeFila {
    Vertice *vertice;
    struct NodeFila *proximo;
} NodeFila;



// CONFIRMADAS
Vertice* CriarVertice(int idVertice, char cidade[]);
Vertice* InsereVertice(Vertice *grafo, Vertice* novo);
Adjacente *CriaAdjacente(int idVertice, float distancia);
Vertice* InsereAdjacente(Vertice *grafo, int origem, Adjacente* novoAdjacente);
const char* GetNomeLocal(Vertice *grafo, int location_id);	
void LimparCamposGrafo(Vertice *grafo);
Caminho* CriarCaminho(int idVertice, float distancia);
int Enfileirar(Fila *fila, Vertice *vertice);
Vertice* RetiraDaFila(Fila *fila);
void PrintGrafo(Vertice *grafo);
int EstaVazia(Fila *fila);
NodeTransporte *ProcuraTransporteMaisProximo(NodeTransporte *listaTransportes, Vertice *grafo, int localCliente);
Caminho* BuscaEmLargura(Vertice *grafo, int origem, int destino);
Fila* CriarFila();
Vertice* ProcuraVertice(Vertice *grafo, int idVertice);
float DistanciaCaminho(Caminho *caminho);

#endif