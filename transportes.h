#ifndef TRANSPORTES_HEADER_GUARD
#define TRANSPORTES_HEADER_GUARD
#include "funcoes.h"

// ESTRUTURA TRANSPORTES
typedef struct Transporte{
    int id;
    char tipo[50];
    int nivelBateria;
    float preco;
    char localizacao[50];
    int estado;
} Transporte;

typedef struct NodeTransporte
{
    struct Transporte transporte;
    struct NodeTransporte *proximo;
}NodeTransporte;



// novas e confirmadas
//struct NodeTransporte* CriarNodeTransporte(struct Transporte transporte);
void InserirNoFimTransporte(struct NodeTransporte** headRef, struct Transporte transporte);
void MostrarTransportes(struct NodeTransporte* head);

#endif