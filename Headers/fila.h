#ifndef FILA_HEADER_GUARD
#define FILA_HEADER_GUARD
#pragma once
#include "grafo.h"

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


Fila* CriarFila();
int Enfileirar(Fila *fila, Vertice *vertice);
int EstaVazia(Fila *fila);
Vertice* RetiraDaFila(Fila *fila);


#endif