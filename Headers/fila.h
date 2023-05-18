#ifndef FILA_HEADER_GUARD
#define FILA_HEADER_GUARD
#pragma once
#include "grafo.h"

// Definição do tipo Fila
typedef struct Fila {
    struct NodeFila *front;
    struct NodeFila *rear;
    Vertice *vertice;
} Fila;

// Definição do tipo NodeFila
typedef struct NodeFila {
    Vertice *vertice;
    struct NodeFila *proximo;
} NodeFila;

typedef struct FilaPrioridade {
    Vertice *vertice;
    struct FilaPrioridade *proximo;
} FilaPrioridade;

Fila* CriarFila();
FilaPrioridade* CriarFilaPrioridade();
Vertice* RetirarDaFila(FilaPrioridade **fila);
int EstaVazia(FilaPrioridade *fila);
FilaPrioridade* AdicionarNaFila(FilaPrioridade *fila, Vertice *vertice);

#endif